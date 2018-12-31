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
        GBuffer(Vector2u dimensions);
        ~GBuffer();

        void bindForWriting() noexcept;
        void bindForReading() noexcept;

    private:
        GLuint m_fbo;

        GLuint m_albedoSpecularTexture;     //[16:Red,16:Green,16:Blue,16:Specular]          = 64bits = 8bytes = GL_RGBA16F
        GLuint m_normalTexture;             //[16:X,16:Y,16:Z]                               = 48bits = 6bytes = GL_RGB16F
        GLuint m_depthStencilTexture;       //[24:depth,8:STENCIL]                           = 32bits = 4bytes = GL_DEPTH_STENCIL_COMPONENT
        //                                                                                            = 18bytes per pixel
        // 1920 * 1080 = 2073600
        // 2073600 * 20 = 41472000
        // 2073600 * 18 = 
        // 2073600 * 16 = 33177600
    };
}