#pragma once

#include <OpenGL/Export.hpp>
#include <Core/Math/Vector.hpp>
#include <Core/Utility/Color.hpp>

#include <GL/glew.h>

namespace ax
{
    class AXION_GL_API RenderBuffer
    {
    public:
        RenderBuffer(Vector2u dimension);
        ~RenderBuffer();

        void bindForWriting() const noexcept;
        void bindForReading() const noexcept;
        void clear(Color3 color) const noexcept;

    private:
        GLuint m_fbo;
        GLuint m_renderTexture;
    };
}