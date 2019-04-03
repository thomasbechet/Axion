#pragma once

#include <OpenGL/Export.hpp>
#include <OpenGL/Renderer/Shader/ShaderGLSL.hpp>

#include <GL/glew.h>

namespace ax
{
    class AXION_GL_API ShaderGL
    {
    public:
        ShaderGLSL shader;
    };
}