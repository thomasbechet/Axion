#pragma once

#include <OpenGL/Export.hpp>
#include <OpenGL/Renderer/Shader/ShaderGLSL.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Renderer/Asset/RendererShader.hpp>

#include <GL/glew.h>

namespace ax
{
    class AXION_GL_API RendererShaderGL : public RendererShader
    {
    public:
        ShaderGLSL shader;

        Id id;
    };
}