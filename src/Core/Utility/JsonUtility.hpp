#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/Json.hpp>
#include <Core/Context/Engine.hpp>
#include <Core/Logger/LoggerModule.hpp>

#include <string>

namespace ax
{
    template<typename T, T dv, std::string type>
    inline T AXION_CORE_API parseValue(const Json& json, const std::string& name, T defaultValue = dv) noexcept
    {
        try
        {
            auto value = json.find(name);
            if(value != json.end())
                return value->get<T>();
            else
                return defaultValue;
        }
        catch(...)
        {
            Engine::logger().log("Failed to parse bool value '" + name + "' from '" + json.get<std::string>(), Severity::Warning);
            return defaultValue;
        }
    }

    using parseBoolean = parseValue<bool, false, "boolean">;
}