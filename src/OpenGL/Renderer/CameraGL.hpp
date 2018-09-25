#pragma once

////////////
//HEADERS
////////////
#include <OpenGL/Export.hpp>
#include <Core/Math/Transform.hpp>
#include <Core/Math/Matrix.hpp>

namespace ax
{
    struct AXION_GL_API CameraGL
    {
        Transform* transform = nullptr;
        Matrix4f projection = Matrix4f::perspective();
    };
}