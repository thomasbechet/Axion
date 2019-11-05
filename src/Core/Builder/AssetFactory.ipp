#pragma once

#include <Core/Builder/AssetFactory.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Asset/AssetModule.ipp>

namespace ax
{
    template<typename A>
    bool AssetFactory<A>::load(const std::string& name, const Json& json) noexcept
    {
        return Engine::asset().load<A>(name, json);
    }
    template<typename A>
    bool AssetFactory<A>::loadAsync(const std::string& name, const Json& json) noexcept
    {
        return Engine::asset().loadAsync<A>(name, json);
    }
    template<typename A>
    bool AssetFactory<A>::unload(const std::string& name) noexcept
    {
        return Engine::asset().unload<A>(name);
    }
    template<typename A>
    bool AssetFactory<A>::exists(const std::string& name) noexcept
    {
        return Engine::asset().exists<A>(name);
    }
    template<typename A>
    bool AssetFactory<A>::wait(const std::string& name) noexcept
    {
        return Engine::asset().wait<A>(name);
    }
    template<typename A>
    void AssetFactory<A>::dispose() noexcept
    {
        Engine::asset().dispose<A>();
    }
    template<typename A>
    void AssetFactory<A>::log() const noexcept
    {
        Engine::asset().log<A>();
    }
}