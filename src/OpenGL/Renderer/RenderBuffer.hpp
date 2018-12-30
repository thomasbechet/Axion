#pragma once

//////////////////
//HEADERS
//////////////////
#include <OpenGL/Export.hpp>
#include <Core/Math/Vector.hpp>

#include <GL/glew.h>

namespace ax
{
    class AXION_GL_API RenderBuffer
    {
    public:
        RenderBuffer(Vector2u dimension);
        ~RenderBuffer();

        void bindForWriting();
        void bindForReading();

    private:
        GLuint m_fbo;

        GLuint m_renderTexture;
    };
}