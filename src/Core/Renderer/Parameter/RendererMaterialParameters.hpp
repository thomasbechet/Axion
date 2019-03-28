#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Utility/Color.hpp>

namespace ax
{
    struct AXION_CORE_API RendererMaterialParameters
    {
        Id diffuseTexture = 0;
        Color3 diffuseColor = Color3(1.0f, 1.0f, 1.0f);
        bool useDiffuseTexture = false;
        bool useDiffuseColor = false;

        Id normalTexture = 0;
        bool useNormalTexture = false;
        bool isBumpTexture = false;

        Id specularTexture = 0;
        float specularUniform = 1.0f;
        bool useSpecularTexture = false;

        Id shader = 0;
    };
}