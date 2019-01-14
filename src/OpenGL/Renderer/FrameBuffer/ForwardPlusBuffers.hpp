#pragma once

////////////////
//HEADERS
////////////////
#include <OpenGL/Export.hpp>
#include <Core/Math/Vector.hpp>

#include <GL/glew.h>

namespace ax
{
    class AXION_GL_API ForwardPlusBuffers
    {
    public:
        ForwardPlusBuffers(Vector2u dimensions);
        ~ForwardPlusBuffers();

        void bindForGeometryPass() noexcept;
        void bindForLightPass() noexcept;
        void bindForPPPass() noexcept;

    private:
        GLuint m_fboGeometry;
        GLuint m_fboLight;

        GLuint m_normalTexture;             //[16:X,16:Y,16:Z]                               = 48bits = 6bytes = GL_RGB16F
        GLuint m_depthStencilTexture;       //[24:depth,8:STENCIL]                           = 32bits = 4bytes = GL_DEPTH_STENCIL_COMPONENT
        GLuint m_lightTexture;              //
    };
}