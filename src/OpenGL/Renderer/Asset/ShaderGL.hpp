#pragma once

#include <OpenGL/Export.hpp>
#include <OpenGL/Renderer/Shader/ShaderGLSL.hpp>

#include <GL/glew.h>

namespace ax
{
    struct AXION_GL_API ShaderGL
    {
        ShaderGLSL shader;
    };
}