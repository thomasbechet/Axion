#pragma once

#include <Core/Export.hpp>
#include <Core/Math/Transform.hpp>
#include <Core/Renderer/Asset/RendererMesh.hpp>
#include <Core/Renderer/Asset/RendererMaterial.hpp>

namespace ax
{
    class AXION_CORE_API RendererStaticmesh
    {
    public:
        virtual void setTransform(Transform* transform) = 0;
        virtual void setMaterial(RendererMaterialHandle material) = 0;
        virtual void setMesh(RendererMeshHandle mesh) = 0;
    };

    class AXION_CORE_API NullRendererStaticMesh : public RendererStaticmesh
    {
    public:
        void setTransform(Transform* transform) override {}
        void setMaterial(RendererMaterialHandle material) override {}
        void setMesh(RendererMeshHandle mesh) override {}
    };

    using RendererStaticmeshHandle = RendererStaticmesh*;
}