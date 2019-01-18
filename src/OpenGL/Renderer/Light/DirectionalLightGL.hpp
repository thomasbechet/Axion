#pragma once

//////////////
//HEADERS
//////////////
#include <OpenGL/Export.hpp>

namespace ax
{
    struct AXION_GL_API DirectionalLightGL
    {
        Vector3f direction;
        Color3 color;

        GLuint uboIndex;
    }; 
}