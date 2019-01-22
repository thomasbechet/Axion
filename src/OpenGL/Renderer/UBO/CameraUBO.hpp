#pragma once

//////////////
//HEADERS
//////////////
#include <OpenGL/Export.hpp>
#include <Core/Math/Matrix.hpp>

#include <GL/glew.h>

namespace ax
{
    class CameraGL;

    class AXION_GL_API CameraUBO
    {
    private:
        struct CameraUBOData
        {
            Matrix4f projectionMatrix;
            Matrix4f viewMatrix;
            Matrix4f invProjectionMatrix;
        };

    public:
        CameraUBO();
        ~CameraUBO();

        void update(const Matrix4f& view, const Matrix4f& projection, const Matrix4f& invProjection) const noexcept;

    private:
        GLuint m_ubo;
    };
}