#include <core/asset/asset_manager.hpp>

namespace ax
{
    template<typename type>
    asset_manager<t>::asset_manager(asset_loader& loader) : m_loader(loader)
    {
        
    }

    template<typename type>
    reference<type> asset_manager<t>::get(const std::string& name) const noexcept
    {
        std::unique_lock<std::mutex> lock(m_mutex);

        if(!exists_not_safe(name))
            engine::interrupt("Failed to access <" + T::identifier + "> '" + name + "' because it doesn't exists");

        asset& asset = *m_assets.at(name).get();
        asset::state state = asset.get_state();

        while(state == asset::state::Pending)
        {
            m_loader.wait(lock);
            state = asset.get_state();
        }

        lock.unlock();

        if(state == asset::state::failed)
        {
            engine::interrupt("Failed to access <" + T::identifier + "> '" + name + "' because it is failed state");
        }
        else if(state == asset::state::unloaded)
        {
            engine::interrupt("Failed to access <" + T::identifier + "> '" + name + "' because it is unloaded");
        }
        else if(state == asset::state::loaded)
        {
            if(!asset.validate())
            {
                engine::interrupt("Failed to access <" + T::identifier + "> '" + name + "' because it could not be validated");
            }
        }

        return m_trackers.at(name)->reference();
    }
    template<typename type>
    bool asset_manager<type>::load(const std::string& name, const typename type::parameters& parameters, bool validate) noexcept
    {
        std::unique_lock<std::mutex> lock(m_mutex);

        if(!exists_not_safe(name))
        {
            m_assets.emplace(name, std::make_unique<T>(name, parameters));
            m_trackers.emplace(name, std::make_unique<reference_tracker<type>>(*m_assets.at(name).get()));

            asset& asset = *m_assets.at(name).get();

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
    template<typename type>
    bool asset_manager<type>::load_async(const std::string& name, const typename type::parameters& parameters) noexcept
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        if(!exists_not_safe(name))
        {
            m_assets.emplace(name, std::make_unique<type>(name, parameters));
            m_trackers.emplace(name, std::make_unique<reference_tracker<type>>(*m_assets.at(name).get()));

            m_loader.add(*m_assets.at(name).get());
            return true;
        }

        return false;
    }
    template<typename type>
    bool asset_manager<type>::exists(const std::string& name) const noexcept
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return exists_not_safe(name);
    }
    template<typename type>
    bool asset_manager<type>::wait(const std::string& name) const noexcept
    {
        std::unique_lock<std::mutex> lock(m_mutex);

        if(exists_not_safe(name))
        {
            asset& asset = *m_assets.at(name).get();

            while(true)
            {
                asset::State state = asset.get_state();
                if(state == asset::state::Validated)
                {
                    return true;
                }
                else if(state == ssset::state::loaded)
                {
                    return asset.validate();
                }
                else if(state == asset::state::pending)
                {
                    m_loader.wait(lock);
                }
                else if(state == asset::state::failed)
                {
                    return false;
                }
            }
        }
        else return false;            
    }
    template<typename type>
    bool asset_manager<type>::unload(const std::string& name) noexcept
    {
        std::unique_lock<std::mutex> lock(m_mutex);

        if(exists_not_safe(name))
        {
            asset& asset = *m_assets.at(name).get();
            if(asset.is_validated())
            {
                if(m_trackers.at(name)->count() == 0)
                {
                    lock.unlock();
                    if(asset.unload())
                    {
                        lock.lock();
                        m_assets.erase(name);
                        m_trackers.erase(name);
                        return true;
                    }
                }
            }
            
            return false;
        }
        
        engine::logger().log("Failed to unload <" + T::identifier + "> '" + name + "' because it doesn't exists", severity::warning);
        return false;
    }

    template<typename type>
    void asset_manager<type>::dispose() noexcept
    {
        std::unique_lock<std::mutex> lock(m_mutex);

        std::vector<std::string> keys;
        keys.reserve(m_assets.size());
        for(auto& it : m_assets)
            keys.emplace_back(it.first);

        lock.unlock();

        for(auto& it : keys) unload(it);
    }
    template<typename type>
    void asset_manager<type>::log() const noexcept
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        const int length = 50;

        std::stringstream ss_title;
        std::string str = " " + type::identifier + " ";

        int len = str.length();
        if(len % 2 == 0) str += " ";
        ss_title << std::setfill('-') << std::setw((length / 2) + (len / 2)) << std::right << str << std::left << std::string(length - ((length / 2) + (len / 2)) - 1, '-'); 
        engine::logger().log(ss_title.str(), severity::info);

        for(auto& it : m_assets)
        {
            asset::state state = it.second->get_state();
            std::string state_string;
            switch(state)
            {
            case asset::state::pending:
                state_string = "[Pending]"; break;
            case asset::state::loaded:
                state_string = "[Loaded]"; break;
            case asset::state::validated:
                state_string = "[Validated]"; break;
            case asset::state::failed:
                state_string = "[Failed]"; break;
            default:
                state_string = "[None]"; break;
            }

            unsigned reference_count = m_trackers.at(it.first)->count();
            state_string += ("[" + std::to_string(reference_count) + "]");

            std::stringstream ss_line;
            ss_line << std::left << std::setw(length - state_string.length() - 1) << ("- '" + it.first + "'") << std::left << state_string;
            engine::logger().log(ss_line.str(), severity::info);
        }
    }

    template<typename type>
    bool asset_manager<type>::exists_not_safe(const std::string& name) const noexcept
    {
        return m_assets.find(name) != m_assets.end();
    }
}