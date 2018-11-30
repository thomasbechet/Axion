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
        Color diffuseUniform;
        bool useDiffuseTexture = false;

        Id normalTexture;
        bool useNormalTexture = false;
        Id bumpTexture;
        bool useBumpTexture = false;
    };
}