#pragma once

#include <Core/Export.hpp>
#include <Core/Math/Geometry/Vertex.hpp>

#include <vector>

namespace ax
{
    class AXION_CORE_API RendererMesh
    {
    public:
        virtual void update(const std::vector<Vertex>& vertices) = 0;
    };

    class AXION_CORE_API NullRendererMesh : public RendererMesh
    {
    public:
        void update(const std::vector<Vertex>& vertices) override {}
    };

    using RendererMeshHandle = RendererMesh*;
}