#include <Core/Utility/JsonUtility.hpp>

#include <fstream>

using namespace ax;

bool JsonUtility::parseFile(const Path& file, Json& json) noexcept
{
    try
    {
        std::ifstream jsonFile(file.str());
        if(!jsonFile.is_open())
        {
            Engine::logger().log("Failed to open file '" + file.str() + "'");
            return false;
        }
        std::string str((std::istreambuf_iterator<char>(jsonFile)),
                         std::istreambuf_iterator<char>());
        json = Json::parse(str);
        return true;
    }
    catch(const std::exception& e)
    {
        Engine::logger().log("Failed to parse '" + file.str() + "': " + e.what(), Severity::Warning);
        return false;
    }
}

bool JsonUtility::readBoolean(const Json& json, const std::string& name, bool defaultValue) noexcept
{
    return readPrimitive<bool>(json, name, defaultValue, "boolean");
}
unsigned JsonUtility::readUnsigned(const Json& json, const std::string& name, unsigned defaultValue) noexcept
{
    return readPrimitive<unsigned>(json, name, defaultValue, "unsigned");
}
int JsonUtility::readInt(const Json& json, const std::string& name, int defaultValue) noexcept
{
    return readPrimitive<int>(json, name, defaultValue, "int");
}
float JsonUtility::readFloat(const Json& json, const std::string& name, float defaultValue) noexcept
{
    return readPrimitive<float>(json, name, defaultValue, "float");
}
double JsonUtility::readDouble(const Json& json, const std::string& name, double defaultValue) noexcept
{
    return readPrimitive<double>(json, name, defaultValue, "double");
}
std::string JsonUtility::readString(const Json& json, const std::string& name, std::string defaultValue) noexcept
{
    return readPrimitive<std::string>(json, name, defaultValue, "string");
}

Vector3f JsonUtility::readVector3f(const Json& json, const std::string& name, Vector3f defaultValue) noexcept
{
    return readObject<Vector3f>(json, name, defaultValue);
}
Vector3f JsonUtility::readVector4f(const Json& json, const std::string& name, Vector4f defaultValue) noexcept
{
    return readObject<Vector4f>(json, name, defaultValue);
}
Quaternionf JsonUtility::readQuaternionf(const Json& json, const std::string& name, Quaternionf defaultValue) noexcept
{
    return readObject<Quaternionf>(json, name, defaultValue);
}
Rectf JsonUtility::readRectf(const Json& json, const std::string& name, Rectf defaultValue) noexcept
{
    return readObject<Rectf>(json, name, defaultValue);
}
Color3 JsonUtility::readColor3(const Json& json, const std::string& name, Color3 defaultValue) noexcept
{
    return readObject<Color3>(json, name, defaultValue);
}
Color4 JsonUtility::readColor4(const Json& json, const std::string& name, Color4 defaultValue) noexcept
{
    return readObject<Color4>(json, name, defaultValue);
}