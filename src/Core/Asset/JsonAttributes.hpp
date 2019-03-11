#pragma once

#include <Core/Export.hpp>

#include <string>

namespace ax
{
    class AXION_CORE_API JsonAttributes
    {
    public:
        static const std::string source;
        static const std::string type;
        static const std::string name;
        static const std::string vertex;
        static const std::string fragment;
        
        static const std::string materialType;
        static const std::string meshType;
        static const std::string modelType;
        static const std::string packageType;
        static const std::string shaderType;
        static const std::string textureType;
    };
}