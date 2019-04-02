#pragma once

#include <OpenGL/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Renderer/Scene/RendererCamera.hpp>

namespace ax
{
    class Transform;

    class AXION_GL_API RendererCameraGL : public RendererCamera
    {
    public:
        void setTransform(Transform* transform) override;
        void setParameters(const RendererCameraParameters& parameters) override;

        Transform* transform = nullptr;

        float fov = 90.0f;
        float near = 0.01f;
        float far = 100.0f;

        Id id;
    };
}