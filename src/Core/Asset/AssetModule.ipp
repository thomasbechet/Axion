#pragma once

#include <Core/Asset/AssetModule.hpp>

namespace ax
{
    template<typename A>
    AssetManager<A>& AssetModule::getManager() noexcept
    {
        std::lock_guard<std::mutex> lock(m_locationMutex);

        std::type_index index = std::type_index(typeid(A));

        if(m_indexes.find(index) != m_indexes.end())
            return static_cast<AssetManager<A>&>(*m_managers.at(m_indexes.at(index)).get());
            

        m_managers.emplace_back(std::make_unique<AssetManager<A>>(loader));
        m_indexes[index] = m_managers.size() - 1;

        return static_cast<AssetManager<A>&>(*m_managers.back().get());
    }

    template<typename A>
    Reference<A> AssetModule::get(const std::string& name) noexcept
    {
        static AssetManager<A>& manager = getManager<A>();
        return manager.get(name);
    }
    template<typename A>
    bool AssetModule::load(const std::string& name, const typename A::Parameters& parameters, bool validate) noexcept
    {
        static AssetManager<A>& manager = getManager<A>();
        return manager.load(name, parameters, validate);
    }
    template<typename A>
    bool AssetModule::loadAsync(const std::string& name, const typename A::Parameters& parameters) noexcept
    {
        static AssetManager<A>& manager = getManager<A>();
        return manager.loadAsync(name, parameters);
    }
    template<typename A>
    bool AssetModule::unload(const std::string& name) noexcept
    {
        static AssetManager<A>& manager = getManager<A>();
        return manager.unload(name);
    }
    template<typename A>
    bool AssetModule::exists(const std::string& name) noexcept
    {
        static AssetManager<A>& manager = getManager<A>();
        return manager.exists(name);
    }
    template<typename A>
    bool AssetModule::wait(const std::string& name) noexcept
    {
        static AssetManager<A>& manager = getManager<A>();
        return manager.wait(name);
    }
    template<typename A>
    void AssetModule::dispose() noexcept
    {
        static AssetManager<A>& manager = getManager<A>();
        return manager.dispose();
    }
    template<typename A>
    void AssetModule::log() noexcept
    {
        static AssetManager<A>& manager = getManager<A>();
        return manager.log();
    }
}