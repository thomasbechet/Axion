#pragma once

#include <Core/Export.hpp>
#include <Core/Math/Transform.hpp>
#include <Core/Renderer/Scene/Parameter/Light/RendererPointLightParameters.hpp>

namespace ax
{
    class AXION_CORE_API RendererPointLight
    {
    public:
        virtual void setTransform(Transform* transform) = 0;
        virtual void setParameters(const RendererPointLightParameters& parameters) = 0;
    };
}