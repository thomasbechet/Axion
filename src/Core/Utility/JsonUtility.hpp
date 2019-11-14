#pragma once

#include <Core/Utility/Json.hpp>
#include <Core/Context/Engine.hpp>
#include <Core/Logger/LoggerModule.hpp>
#include <Core/Math/Vector.hpp>
#include <Core/Math/Quaternion.hpp>
#include <Core/Math/Rect.hpp>
#include <Core/Utility/Color.hpp>

namespace ax
{
    namespace JsonUtility
    {
        template<typename T>
        inline T readPrimitive(const Json& json, const std::string& name, const T& defaultValue, const std::string& displayType) noexcept
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
                Engine::logger().log("Failed to parse " + displayType + " '" + name + "'", Severity::Warning);
                return defaultValue;
            }
        }
        template<typename T>
        inline T readObject(const Json& json, const std::string& name, const T& defaultValue) noexcept
        {
            auto value = json.find(name);
            if(value != json.end())
                return T::parse(*value);
            else
                return defaultValue;
        }   

        inline bool readBoolean(const Json& json, const std::string& name, bool defaultValue = false) noexcept
        {
            return readPrimitive<bool>(json, name, defaultValue, "boolean");
        }
        inline float readFloat(const Json& json, const std::string& name, float defaultValue = 0.0f) noexcept
        {
            return readPrimitive<float>(json, name, defaultValue, "float");
        }
        inline double readDouble(const Json& json, const std::string& name, double defaultValue = 0.0) noexcept
        {
            return readPrimitive<double>(json, name, defaultValue, "double");
        }
        inline std::string readString(const Json& json, const std::string& name, std::string defaultValue = "") noexcept
        {
            return readPrimitive<std::string>(json, name, defaultValue, "string");
        }

        inline Vector3f readVector3f(const Json& json, const std::string& name, Vector3f defaultValue = Vector3f()) noexcept
        {
            return readObject<Vector3f>(json, name, defaultValue);
        }
        inline Vector3f readVector4f(const Json& json, const std::string& name, Vector4f defaultValue = Vector4f()) noexcept
        {
            return readObject<Vector4f>(json, name, defaultValue);
        }
        inline Quaternionf readQuaternionf(const Json& json, const std::string& name, Quaternionf defaultValue = Quaternionf()) noexcept
        {
            return readObject<Quaternionf>(json, name, defaultValue);
        }
        inline Rectf readRectf(const Json& json, const std::string& name, Rectf defaultValue = Rectf()) noexcept
        {
            return readObject<Rectf>(json, name, defaultValue);
        }
        inline Color3 readColor3(const Json& json, const std::string& name, Color3 defaultValue = Color3()) noexcept
        {
            return readObject<Color3>(json, name, defaultValue);
        }
        inline Color4 readColor4(const Json& json, const std::string& name, Color4 defaultValue = Color4()) noexcept
        {
            return readObject<Color4>(json, name, defaultValue);
        }
    }
    
}