#pragma once

/////////////
//HEADERS
/////////////
#include <Core/Export.hpp>
#include <Core/Utility/Color.hpp>

namespace ax
{
    struct AXION_CORE_API PointLightParameters
    {
        Color color = Color(1.0f, 1.0f, 1.0f);
        float radius = 10.0f;
    };
}