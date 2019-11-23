#pragma once

#include <Core/Export.hpp>
#include <Core/Content/Component/TransformComponent.hpp>

namespace ax
{
    struct AXION_CORE_API RendererCameraParameters
    {
        float fov = 90.0f;
        float near = 0.01f;
        float far = 100.0f;
    };

    class AXION_CORE_API RendererCamera
    {
    public:
        virtual void setTransform(TransformComponent* transform) = 0;
        virtual void setParameters(const RendererCameraParameters& parameters) = 0;
    };

    class AXION_CORE_API NullRendererCamera : public RendererCamera
    {
    public:
        void setTransform(TransformComponent* transform) override {}
        void setParameters(const RendererCameraParameters& parameters) override {}
    };

    using RendererCameraHandle = RendererCamera*;
}