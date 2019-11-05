#include <Core/Asset/AssetModule.hpp>

namespace ax
{
    template<typename A>
    size_t AssetModule::generateManagerLocation() noexcept
    {
        m_managers.emplace_back(std::make_unique<AssetManager<A>>(loader));
        return m_managers.size() - 1;
    }
    template<typename A>
    AssetManager<A>& AssetModule::getManager() noexcept
    {
        std::lock_guard<std::mutex> lock(m_locationMutex);
        static size_t location = generateManagerLocation<A>();
        return *m_managers.at(location).get();
    }

    template<typename A>
    AssetReference<A> AssetModule::get(const std::string& name) const noexcept
    {
        static AssetManager<A>& manager = getManager<A>();
        return manager.get(name);
    }
    template<typename A>
    bool AssetModule::load(const std::string& name, const typename A::Parameters& parameters) noexcept
    {
        static AssetManager<A>& manager = getManager<A>();
        return manager.load(name, parameters);
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