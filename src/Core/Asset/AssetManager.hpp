#pragma once

#include <Core/Export.hpp>
#include <Core/Asset/AssetLoader.hpp>
#include <Core/Asset/AssetReference.hpp>
#include <Core/Logger/Logger.hpp>

#include <mutex>
#include <unordered_map>

namespace ax
{
    template<typename T>
    class AXION_CORE_API AssetManager
    {
    public:
        AssetManager(AssetLoader& assetLoader) : m_assetLoader(assetLoader) {}

        //MAIN THREAD ONLY
        AssetReference<T> operator()(std::string name) const noexcept
        {
            std::unique_lock<std::mutex> lock(m_mutex);

            if(existsNotSafe(name))
            {
                Asset& asset = *m_assets.at(name)->get();
                Asset::State state = asset.getState();

                while(state == Asset::State::Pending)
                {
                    m_assetLoader.wait(lock);
                    state = asset.getState();
                }

                lock.unlock();

                if(state == Asset::State::Loaded)
                {
                    if(asset.validate())
                    {
                        return m_assets.at(name)->reference();
                    }
                    else
                    {
                        Engine::logger().log("Failed to validate <" + T::name + "> '" + name + "'", Logger::Warning);
                        asset.error();
                    }
                }
                else if(state == Asset::State::Validated)
                {
                    return m_assets.at(name)->reference();
                }
                else if(state == Asset::State::Failed)
                {
                    Engine::logger().log("Failed to load <" + T::name + "> '" + name + "'", Logger::Warning);
                    asset.error();
                }

                Engine::interrupt("Failed to access <" + T::name + "> '" + name + "'");
            }
            else
            {
                Engine::interrupt("Failed to access <" + T::name + "> '" + name + "' because it doesn't exists");
            }
        }
        //ANY THREAD (validate = ONLY MAIN THREAD)
        bool load(std::string name, const typename T::Parameters& parameters, bool validate = false) noexcept
        {
            std::unique_lock<std::mutex> lock(m_mutex);

            if(!existsNotSafe(name))
            {
                m_assets.emplace(name, std::make_unique<AssetHolder<T>>(name, parameters));
                Asset& asset = *m_assets.at(name)->get();

                lock.unlock();

                if(asset.load())
                {
                    if(validate)
                    {
                        if(!asset.validate())
                        {
                            asset.error();
                            return false;
                        }
                        else
                        {
                            return true;
                        }
                    }
                    else 
                    {
                        return true;
                    }
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        //ANY THREAD
        bool loadAsync(std::string name, const typename T::Parameters& parameters) noexcept
        {
            std::lock_guard<std::mutex> lock(m_mutex);

            if(!existsNotSafe(name))
            {
                m_assets.emplace(name, std::make_unique<AssetHolder<T>>(name, parameters));
                m_assetLoader.add(*m_assets.at(name)->get());
                return true;
            }
            else
            {
                return false;
            }
        }
        //ANY THREAD
        bool exists(std::string name) const noexcept
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            return existsNotSafe(name); 
        }
        //MAIN THREAD ONLY
        bool wait(std::string name) const noexcept
        {
            std::unique_lock<std::mutex> lock(m_mutex);

            if(existsNotSafe(name))
            {
                Asset& asset = *m_assets.at(name)->get();

                while(true)
                {
                    Asset::State state = asset.getState();
                    if(state == Asset::State::Validated)
                    {
                        return true;
                    }
                    else if(state == Asset::State::Loaded)
                    {
                        return asset.validate();
                    }
                    else if(state == Asset::State::Pending)
                    {
                        m_assetLoader.wait(lock);
                    }
                    else if(state == Asset::State::Failed)
                    {
                        asset.error();
                        return false;
                    }
                }
            }
            else
            {
                return false;
            }            
        }
        //MAIN THREAD ONLY
        bool unload(std::string name) noexcept
        {
            std::unique_lock<std::mutex> lock(m_mutex);

            if(existsNotSafe(name))
            {
                Asset& asset = *m_assets.at(name)->get();
                if(asset.isValidated())
                {
                    if(m_assets.at(name)->referenceCount() == 0)
                    {
                        lock.unlock();
                        if(asset.unload())
                        {
                            lock.lock();
                            m_assets.erase(name);
                            return true;
                        }
                    }
                }
                else
                {
                    return false;
                }
            }
            else
            {
                Engine::logger().log("Failed to unload <" + T::name + "> '" + name + "' because it doesn't exists.", Logger::Warning);
                return false;
            }

            return false;
        }

        //MAIN THREAD ONLY
        void dispose() noexcept
        {
            std::unique_lock<std::mutex> lock(m_mutex);

            std::vector<std::string> keys;
            keys.reserve(m_assets.size());
            for(auto& it : m_assets)
                keys.emplace_back(it.first);

            lock.unlock();

            for(auto& it : keys) unload(it);
        }
        //MAIN THREAD ONLY
        void log() const noexcept
        {
            std::lock_guard<std::mutex> lock(m_mutex);

            Engine::logger().log("=============== " + T::name + " ===============", Logger::Info);
    
            for(auto& it : m_assets)
            {
                Asset::State state = it.second->get()->getState();
                std::string stateString;
                switch(state)
                {
                case Asset::State::Pending:
                    stateString = "[Pending]   "; break;
                case Asset::State::Loaded:
                    stateString = "[Loaded]    "; break;
                case Asset::State::Validated:
                    stateString = "[Validated] "; break;
                case Asset::State::Failed:
                    stateString = "[Failed]    "; break;
                default:
                    stateString = "[None]      "; break;
                }
                Engine::logger().log("- " + stateString + "'" + it.first + "'", Logger::Info);
            }
        }
        
    private:
        bool existsNotSafe(const std::string& name) const noexcept
        {
            return m_assets.find(name) != m_assets.end();
        }

    private:
        std::unordered_map<std::string, std::unique_ptr<AssetHolder<T>>> m_assets;
        mutable std::mutex m_mutex;
        AssetLoader& m_assetLoader;
    };
}