#pragma once

//////////////
//HEADERS
//////////////
#include <OpenGL/Export.hpp>
#include <Core/Math/Transform.hpp>

namespace ax
{
    struct AXION_GL_API DirectionalLightGL
    {
        Transform* transform = nullptr;

        Color3 color;

        GLuint uboIndex;
    }; 
}