#pragma once

////////////
//HEADERS
////////////
#include <OpenGL/Export.hpp>
#include <OpenGL/Renderer/Utility/ShaderGLSL.hpp>

#include <GL/glew.h>

namespace ax
{
    struct AXION_GL_API ShaderGL
    {
        ShaderGLSL shader;
    };
}