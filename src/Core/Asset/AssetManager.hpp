#pragma once

#include <Core/Export.hpp>
#include <Core/Asset/AssetLoader.hpp>
#include <Core/Asset/AssetReference.hpp>
#include <Core/Logger/LoggerModule.hpp>

#include <mutex>
#include <unordered_map>
#include <sstream>
#include <iomanip>

namespace ax
{
    template<typename T>
    class AXION_CORE_API AssetManager
    {
    public:
        AssetManager(AssetLoader& loader) : m_loader(loader) {}

        //MAIN THREAD ONLY
        AssetReference<T> operator()(std::string name) const noexcept
        {
            std::unique_lock<std::mutex> lock(m_mutex);

            if(!existsNotSafe(name))
            {
                Engine::interrupt("Failed to access <" + T::identifier + "> '" + name + "' because it doesn't exists");
            }

            Asset& asset = *m_assets.at(name)->get();
            Asset::State state = asset.getState();

            while(state == Asset::State::Pending)
            {
                m_loader.wait(lock);
                state = asset.getState();
            }

            lock.unlock();

            if(state == Asset::State::Failed)
            {
                Engine::interrupt("Failed to access <" + T::identifier + "> '" + name + "' because it is failed state");
            }
            else if(state == Asset::State::Unloaded)
            {
                Engine::interrupt("Failed to access <" + T::identifier + "> '" + name + "' because it is unloaded");
            }
            else if(state == Asset::State::Loaded)
            {
                if(!asset.validate())
                {
                    Engine::interrupt("Failed to access <" + T::identifier + "> '" + name + "' because it could not be validated");
                }
            }

            return m_assets.at(name)->reference(); 
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
                        return asset.validate();
                    }
                    
                    return true;
                }
                
                return false;
            }
            
            return false;
        }
        //ANY THREAD
        bool loadAsync(std::string name, const typename T::Parameters& parameters) noexcept
        {
            std::lock_guard<std::mutex> lock(m_mutex);

            if(!existsNotSafe(name))
            {
                m_assets.emplace(name, std::make_unique<AssetHolder<T>>(name, parameters));
                m_loader.add(*m_assets.at(name)->get());
                return true;
            }

            return false;
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
                        m_loader.wait(lock);
                    }
                    else if(state == Asset::State::Failed)
                    {
                        return false;
                    }
                }
            }
            else return false;            
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
                
                return false;
            }
            
            Engine::logger().log("Failed to unload <" + T::identifier + "> '" + name + "' because it doesn't exists", Severity::Warning);
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

            const int length = 50;

            std::stringstream ssTitle;
            std::string str = " " + T::identifier + " ";

            int len = str.length();
            if(len % 2 == 0) str += " ";
            ssTitle << std::setfill('-') << std::setw((length / 2) + (len / 2)) << std::right << str << std::left << std::string(length - ((length / 2) + (len / 2)) - 1, '-'); 
            Engine::logger().log(ssTitle.str(), Severity::Info);
    
            for(auto& it : m_assets)
            {
                Asset::State state = it.second->get()->getState();
                std::string stateString;
                switch(state)
                {
                case Asset::State::Pending:
                    stateString = "[Pending]"; break;
                case Asset::State::Loaded:
                    stateString = "[Loaded]"; break;
                case Asset::State::Validated:
                    stateString = "[Validated]"; break;
                case Asset::State::Failed:
                    stateString = "[Failed]"; break;
                default:
                    stateString = "[None]"; break;
                }

                stateString += ("[" + std::to_string(it.second.get()->referenceCount()) + "]");

                std::stringstream ssLine;
                ssLine << std::left << std::setw(length - stateString.length() - 1) << ("- '" + it.first + "'") << std::left << stateString;
                Engine::logger().log(ssLine.str(), Severity::Info);
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
        AssetLoader& m_loader;
    };
}