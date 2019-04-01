#pragma once

#include <Core/Export.hpp>
#include <Core/Renderer/Asset/Parameter/RendererMaterialParameters.hpp>

namespace ax
{
    class AXION_CORE_API RendererMaterial
    {
    public:
        virtual void update(const RendererMaterialParameters& settings) = 0;
    };

    class AXION_CORE_API NullRendererMaterial : public RendererMaterial
    {
    public:
        void update(const RendererMaterialParameters& settings) override {}
    };

    using RendererMaterialHandle = RendererMaterial*;
}