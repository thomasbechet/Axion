#pragma once

//////////////
//HEADERS
//////////////
#include <OpenGL/Export.hpp>
#include <Core/Math/Matrix.hpp>

#include <GL/glew.h>

#define CAMERA_BINDING_POINT 3

namespace ax
{
    class CameraGL;

    class AXION_GL_API CameraUBO
    {
    private:
        struct CameraUBOData
        {
            Matrix4f viewMatrix;
            Matrix4f projectionMatrix;
            Matrix4f invViewMatrix;
            Matrix4f invProjectionMatrix;
        };

    public:
        CameraUBO();
        ~CameraUBO();

        void update(const Matrix4f& view, const Matrix4f& projection) noexcept;

    private:
        GLuint m_ubo;
    };
}