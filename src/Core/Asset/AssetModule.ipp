#include <Core/Asset/AssetModule.hpp>

#include <iostream>

namespace ax
{
    template<typename A>
    size_t AssetModule::generateManager() noexcept
    {
        m_managers.emplace_back(std::make_unique<AssetManager<A>>(loader));
        std::cout << "generate " << A::identifier << std::endl;
        return m_managers.size() - 1;
    }
    template<typename A>
    AssetManager<A>& AssetModule::getManager() noexcept
    {
        std::lock_guard<std::mutex> lock(m_locationMutex);
        static size_t location = generateManager<A>();
        std::cout << "location: " << location << " type: " << A::identifier << std::endl;
        return static_cast<AssetManager<A>&>(*m_managers.at(location).get());
    }

    template<typename A>
    AssetReference<A> AssetModule::get(const std::string& name) noexcept
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
    void AssetModule::log() const noexcept
    {
        static AssetManager<A>& manager = getManager<A>();
        return manager.log();
    }
}