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
        Color diffuseColor;
        bool useDiffuseTexture = false;

        Id normalTexture;
        bool useNormalTexture = false;
    };
}