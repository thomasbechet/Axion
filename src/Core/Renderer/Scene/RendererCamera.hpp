#pragma once

#include <Core/Export.hpp>
#include <Core/Math/Transform.hpp>
#include <Core/Renderer/Scene/Parameter/RendererCameraParameters.hpp>

namespace ax
{
    class AXION_CORE_API RendererCamera
    {
    public:
        virtual void setTransform(Transform* transform) = 0;
        virtual void setParameters(const RendererCameraParameters& parameters) = 0;
    };

    class AXION_CORE_API NullRendererCamera : public RendererCamera
    {
    public:
        void setTransform(Transform* transform) override {}
        void setParameters(const RendererCameraParameters& parameters) override {}
    };

    using RendererCameraHandle = RendererCamera*;
}