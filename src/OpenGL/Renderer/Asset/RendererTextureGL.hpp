#pragma once

#include <OpenGL/Export.hpp>
#include <Core/Renderer/Asset/RendererTexture.hpp>

#include <GL/glew.h>

namespace ax
{
    class AXION_GL_API RendererTextureGL : public RendererTexture
    {
    public:
        GLuint texture;

        Id id;
    };
}