#pragma once

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
        void bindForCullPass() noexcept;
        void bindForLightPass() noexcept;
        void bindForPPPass() noexcept;

    private:
        GLuint m_fboGeometry;
        GLuint m_fboLight;

        GLuint m_normalTexture;          
        GLuint m_depthTexture;              
        GLuint m_lightAccumulationTexture;              
    };
}