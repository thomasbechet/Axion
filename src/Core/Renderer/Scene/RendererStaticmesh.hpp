#pragma once

#include <Core/Export.hpp>
#include <Core/Math/Transform.hpp>

namespace ax
{
    using RendererStaticmeshPointer = RendererStaticmesh*;

    class AXION_CORE_API RendererStaticmesh
    {
    public:
        virtual void setTransform(Transform* transform) = 0;
        virtual void setMaterial(Id id, Id material) = 0;
        virtual void setMaterial(Id id, Id material) = 0;
        virtual void setMesh(Id id, Id mesh) = 0;
    };
}