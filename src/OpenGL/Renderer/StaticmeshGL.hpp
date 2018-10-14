#pragma once

/////////////
//HEADERS
/////////////
#include <OpenGL/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Math/Transform.hpp>

namespace ax
{
    struct AXION_GL_API StaticmeshGL
    {
        Transform* transform = nullptr;
        Id mesh = 0;
        Id material = 0;
    };
}