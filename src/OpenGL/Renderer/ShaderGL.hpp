#pragma once

////////////
//HEADERS
////////////
#include <OpenGL/Export.hpp>
#include <OpenGL/Renderer/Utility/ShaderHolder.hpp>

#include <GL/glew.h>

namespace ax
{
    struct AXION_GL_API ShaderGL
    {
        ShaderHolder shader;
    };
}