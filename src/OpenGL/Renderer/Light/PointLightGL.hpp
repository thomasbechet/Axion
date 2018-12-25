#pragma once

///////////////
//HEADERS
///////////////
#include <OpenGL/Export.hpp>
#include <Core/Math/Transform.hpp>

namespace ax
{
    struct AXION_GL_API PointLightGL
    {
        Transform* transform = nullptr;

        Color color;
        float radius;
        float intensity;

        GLuint uboIndex;
    };
}