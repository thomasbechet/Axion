#pragma once

/////////////
//HEADERS
/////////////
#include <Core/Export.hpp>
#include <Core/Math/Vector.hpp>

namespace ax
{
    struct AXION_CORE_API Vertex
    {
        Vector3f position;
        Vector2f uv;
        Vector3f normal;
        Vector3f color;
    };
}