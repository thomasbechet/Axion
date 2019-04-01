#pragma once

#include <Core/Export.hpp>
#include <Core/Math/Transform.hpp>
#include <Core/Renderer/Scene/Parameter/RendererCameraParameters.hpp>

namespace ax
{
    using RendererCameraPointer = RendererCamera*;

    class AXION_CORE_API RendererCamera
    {
    public:
        virtual void setTransform(Transform* transform) = 0;
        virtual void setParameters(const RendererCameraParameters& parameters) = 0;
    };
}