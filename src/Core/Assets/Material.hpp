#pragma once

////////////
//HEADERS
////////////
#include <Core/Export.hpp>
#include <Core/Utility/Observer.hpp>

#include <memory>

namespace ax
{
    struct AXION_CORE_API MaterialData
    {
        std::string diffuseTexture = "";
        Color diffuseUniform = Color(1.0f, 1.0f, 1.0f);
        
        std::string normalTexture = "";
    };

    struct AXION_CORE_API Material
    {
        std::shared_ptr<const Texture> diffuseTexture = nullptr;
        Color diffuseUniform = Color(1.0f, 1.0f, 1.0f, 1.0f);
        
        std::shared_ptr<const Texture> normalTexture = nullptr;
    };
}