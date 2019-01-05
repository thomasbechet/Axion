#pragma once

/////////////
//HEADERS
/////////////
#include <Core/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Utility/Color.hpp>

namespace ax
{
    struct AXION_CORE_API RendererMaterialParameters
    {
        Id diffuseTexture;
        Color3 diffuseColor;
        bool useDiffuseTexture = false;

        Id normalTexture;
        bool useNormalTexture = false;
        bool isBumpTexture = false;

        Id specularTexture;
        float specularUniform;
        bool useSpecularTexture = false;
    };
}