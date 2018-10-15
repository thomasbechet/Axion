#pragma once

////////////
//HEADERS
////////////
#include <OpenGL/Export.hpp>

namespace ax
{
    struct AXION_GL_API MaterialGL
    {
        bool diffuseUseTexture;
        Color diffuseColor;
        GLint diffuseTexture;
    };
}