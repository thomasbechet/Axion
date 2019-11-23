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
        bool parseFile(const Path& file, Json& json) noexcept;

        template<typename T>
        T readPrimitive(const Json& json, const std::string& name, const T& defaultValue, const std::string& displayType) noexcept
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
        T readObject(const Json& json, const std::string& name, const T& defaultValue) noexcept
        {
            try
            {
                auto value = json.find(name);
                if(value != json.end())
                    return T::parse(*value);
                else
                    return defaultValue;
            }
            catch(...)
            {
                Engine::logger().log("Failed to parse '" + name + "'", Severity::Warning);
                return defaultValue;
            }
        }   

        bool readBoolean(const Json& json, const std::string& name, bool defaultValue = false) noexcept;
        unsigned readUnsigned(const Json& json, const std::string& name, unsigned defaultValue = 0) noexcept;
        int readInt(const Json& json, const std::string& name, int defaultValue = 0) noexcept;
        float readFloat(const Json& json, const std::string& name, float defaultValue = 0.0f) noexcept;
        double readDouble(const Json& json, const std::string& name, double defaultValue = 0.0) noexcept;
        std::string readString(const Json& json, const std::string& name, std::string defaultValue = "") noexcept;

        Vector3f readVector3f(const Json& json, const std::string& name, Vector3f defaultValue = Vector3f()) noexcept;
        Vector3f readVector4f(const Json& json, const std::string& name, Vector4f defaultValue = Vector4f()) noexcept;
        Quaternionf readQuaternionf(const Json& json, const std::string& name, Quaternionf defaultValue = Quaternionf()) noexcept;
        Rectf readRectf(const Json& json, const std::string& name, Rectf defaultValue = Rectf()) noexcept;
        Color3 readColor3(const Json& json, const std::string& name, Color3 defaultValue = Color3()) noexcept;
        Color4 readColor4(const Json& json, const std::string& name, Color4 defaultValue = Color4()) noexcept;
    }
}