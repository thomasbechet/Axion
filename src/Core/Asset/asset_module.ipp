#pragma once

#include <core/asset/asset_module.hpp>

namespace ax::detail
{
    template<typename type>
    asset_manager<type>& asset_module::get_manager() noexcept
    {
        std::lock_guard<std::mutex> lock(m_location_mutex);

        std::type_index index = std::type_index(typeid(type));

        if(m_indexes.find(index) != m_indexes.end())
            return static_cast<asset_manager<type>&>(*m_managers.at(m_indexes.at(index)).get());
            

        m_managers.emplace_back(std::make_unique<asset_manager<type>>(loader));
        m_indexes[index] = m_managers.size() - 1;

        return static_cast<asset_manager<type>&>(*m_managers.back().get());
    }

    template<typename type>
    reference<type> asset_module::get(const std::string& name) noexcept
    {
        static asset_manager<a>& manager = get_manager<type>();
        return manager.get(name);
    }
    template<typename type>
    bool asset_module::load(const std::string& name, const typename type::parameters& parameters, bool validate) noexcept
    {
        static asset_manager<type>& manager = get_manager<type>();
        return manager.load(name, parameters, validate);
    }
    template<typename type>
    bool asset_module::load_async(const std::string& name, const typename type::parameters& parameters) noexcept
    {
        static asset_manager<type>& manager = get_manager<type>();
        return manager.load_async(name, parameters);
    }
    template<typename type>
    bool asset_module::unload(const std::string& name) noexcept
    {
        static asset_manager<type>& manager = get_manager<type>();
        return manager.unload(name);
    }
    template<typename type>
    bool asset_module::exists(const std::string& name) noexcept
    {
        static asset_manager<type>& manager = get_manager<type>();
        return manager.exists(name);
    }
    template<typename type>
    bool asset_module::wait(const std::string& name) noexcept
    {
        static asset_manager<type>& manager = get_manager<type>();
        return manager.wait(name);
    }
    template<typename type>
    void asset_module::dispose() noexcept
    {
        static asset_manager<type>& manager = get_manager<type>();
        return manager.dispose();
    }
    template<typename type>
    void asset_module::log() noexcept
    {
        static asset_manager<type>& manager = get_manager<type>();
        return manager.log();
    }
}