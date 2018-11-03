#pragma once

////////////////
//HEADERS
////////////////
#include <OpenGL/Export.hpp>
#include <Core/Math/Vector.hpp>

#include <GL/glew.h>

namespace ax
{
    class AXION_GL_API GBuffer
    {
    public:
        enum TextureType
        {
            Albedo,
            Normal,
            Position,
            Depth
        };

        GBuffer(Vector2u dimensions);
        ~GBuffer();

        void bindForWriting() noexcept;
        void bindForReading() noexcept;

    private:
        GLuint m_fbo;

        GLuint m_albedoTexture;
        GLuint m_normalTexture;
        GLuint m_positionTexture;
        GLuint m_depthTexture;
    };
}