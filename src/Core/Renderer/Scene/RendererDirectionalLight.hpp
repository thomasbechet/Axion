#pragma once

#include <Core/Export.hpp>
#include <Core/Math/Transform.hpp>
#include <Core/Renderer/Scene/Parameter/Light/RendererDirectionalLightParameters.hpp>

namespace ax
{
    using RendererDirectionalLightPointer = RendererDirectionalLight*;

    class AXION_CORE_API RendererDirectionalLight
    {
    public:
        virtual void setTransform(Transform* transform) = 0;
        virtual void setParameters(const RendererDirectionalLightParameters& parameters) = 0;
    };
}