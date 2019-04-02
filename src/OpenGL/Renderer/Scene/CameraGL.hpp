#pragma once

#include <OpenGL/Export.hpp>
#include <Core/Math/Transform.hpp>
#include <Core/Math/Matrix.hpp>

namespace ax
{
    struct AXION_GL_API CameraGL
    {
        Transform* transform = nullptr;

        float fov = 90.0f;
        float near = 0.01f;
        float far = 100.0f;
    };
}