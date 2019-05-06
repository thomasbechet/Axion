#pragma once

#include <OpenGL/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Renderer/Asset/RendererTexture.hpp>
#include <Core/Math/Vector.hpp>

#include <GL/glew.h>

namespace ax
{
    class AXION_GL_API RendererTextureGL : public RendererTexture
    {
    public:
        GLuint texture;
        Vector2u size;

        Id id;
    };
}