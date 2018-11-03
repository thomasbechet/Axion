#pragma once

//////////////
//HEADERS
//////////////
#include <OpenGL/Export.hpp>

namespace ax
{
    struct AXION_GL_API WireframePassData
    {
        GLuint shader;
        GLuint viewLocation;
        GLuint projectionLocation;
        GLuint transformLocation;
    };
}