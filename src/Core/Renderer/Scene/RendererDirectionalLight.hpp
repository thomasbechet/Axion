#pragma once

#include <Core/Export.hpp>
#include <Core/Math/Transform.hpp>
#include <Core/Renderer/Scene/Parameter/Light/RendererDirectionalLightParameters.hpp>

namespace ax
{
    class AXION_CORE_API RendererDirectionalLight
    {
    public:
        virtual void setTransform(Transform* transform) = 0;
        virtual void setParameters(const RendererDirectionalLightParameters& parameters) = 0;
    };

    class AXION_CORE_API NullRendererDirectionalLight : public RendererDirectionalLight
    {
    public:
        void setTransform(Transform* transform) override {}
        void setParameters(const RendererDirectionalLightParameters& parameters) override {}
    };

    using RendererDirectionalLightHandle = RendererDirectionalLight*;
}