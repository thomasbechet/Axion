#pragma once

#include <Core/Export.hpp>
#include <Core/Math/Vector.hpp>
#include <Core/Utility/Color.hpp>

namespace ax
{
    struct AXION_CORE_API Vertex2D
    {
        Vector2f position;
        Vector2f uv;
        Color3 color;
    };
}