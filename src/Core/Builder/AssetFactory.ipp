#pragma once

#include <Core/Builder/AssetFactory.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Asset/AssetModule.ipp>
#include <Core/Asset/JsonAttributes.hpp>

namespace ax
{
    template<typename A>
    BasicReference AssetFactory<A>::get(const std::string& name) noexcept
    {
        return Engine::asset().get<A>(name);
    }
    template<typename A>
    bool AssetFactory<A>::load(const Json& json, bool validate) noexcept
    {
        try
        {
            std::string name = json.find(JsonAttributes::name)->get<std::string>();
            typename A::Parameters parameters;
            parameters.json = json;
            return Engine::asset().load<A>(name, parameters, validate);
        }
        catch(const std::exception& e)
        {
            Engine::logger().log("Failed to load asset <" + A::identifier + "> because json doesn't have '" + JsonAttributes::name + "' attribute", Severity::Warning);
            return false;
        }
    }
    template<typename A>
    bool AssetFactory<A>::loadAsync(const Json& json) noexcept
    {
        try
        {
            std::string name = json.find(JsonAttributes::name)->get<std::string>();
            typename A::Parameters parameters;
            parameters.json = json;
            return Engine::asset().loadAsync<A>(name, parameters);
        }
        catch(const std::exception& e)
        {
            Engine::logger().log("Failed to load async asset <" + A::identifier + "> because json doesn't have '" + JsonAttributes::name + "' attribute", Severity::Warning);
            return false;
        }
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