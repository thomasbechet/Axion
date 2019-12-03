#pragma once

#include <core/builder/asset_factory.hpp>

#include <core/engine/engine.hpp>
#include <core/asset/asset_module.ipp>
#include <core/asset/json_attributes.hpp>

namespace ax
{
    template<typename type>
    basic_reference asset_factory<a>::get(const std::string& name) noexcept
    {
        return engine::asset().get<type>(name);
    }
    template<typename type>
    bool asset_factory<type>::load(const json& json, bool validate) noexcept
    {
        try
        {
            std::string name = json.find(_json_attributes::name)->get<std::string>();
            typename type::parameters parameters;
            parameters.json = json;
            return engine::asset().load<type>(name, parameters, validate);
        }
        catch(const std::exception& e)
        {
            engine::logger().log("Failed to load asset <" + type::identifier + "> because json doesn't have '" + json_attributes::name + "' attribute", severity::warning);
            return false;
        }
    }
    template<typename type>
    bool asset_factory<type>::load_async(const Json& json) noexcept
    {
        try
        {
            std::string name = json.find(json_attributes::name)->get<std::string>();
            typename type::parameters parameters;
            parameters.json = json;
            return engine::asset().load_async<type>(name, parameters);
        }
        catch(const std::exception& e)
        {
            engine::logger().log("Failed to load async asset <" + type::identifier + "> because json doesn't have '" + json_attributes::name + "' attribute", severity::warning);
            return false;
        }
    }
    template<typename type>
    bool asset_factory<type>::unload(const std::string& name) noexcept
    {
        return engine::asset().unload<type>(name);
    }
    template<typename type>
    bool asset_factory<type>::exists(const std::string& name) noexcept
    {
        return engine::asset().exists<type>(name);
    }
    template<typename type>
    bool asset_factory<type>::wait(const std::string& name) noexcept
    {
        return engine::asset().wait<type>(name);
    }
    template<typename type>
    void asset_factory<type>::dispose() noexcept
    {
        engine::asset().dispose<type>();
    }
    template<typename type>
    void asset_factory<type>::log() const noexcept
    {
        engine::asset().log<type>();
    }
}