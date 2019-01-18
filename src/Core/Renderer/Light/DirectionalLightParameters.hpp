#pragma once

/////////////
//HEADERS
/////////////
#include <Core/Export.hpp>

namespace ax
{
    struct AXION_CORE_API DirectionalLightParameters
    {
        Vector3f direction = Vector3f::down;
        Color3 color = = Color3(1.0f, 1.0f, 1.0f);
        float intensity = 1.0f;
    };
}