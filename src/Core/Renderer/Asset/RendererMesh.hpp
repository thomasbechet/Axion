#pragma once

#include <Core/Export.hpp>

namespace ax
{
    using RendererMeshPointer = RendererMesh*;

    class AXION_CORE_API RendererMesh
    {
    public:
        virtual void update(Id id, const std::vector<Vertex>& vertices) = 0;
    };
}