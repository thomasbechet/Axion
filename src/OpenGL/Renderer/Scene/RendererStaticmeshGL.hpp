#pragma once

#include <OpenGL/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Renderer/Asset/RendererMaterial.hpp>
#include <Core/Renderer/Scene/RendererStaticmesh.hpp>

namespace ax
{
    class Transform;
    class RendererMeshGL;
    class RendererMaterialGL;
    class RenderContent;

    class AXION_GL_API RendererStaticmeshGL : public RendererStaticmesh
    {
    public:
        void setTransform(Transform* transform) override;
        void setMaterial(RendererMaterialHandle material) override;
        void setMesh(RendererMeshHandle mesh) override;

        Transform* transform = nullptr;
        RendererMeshGL* mesh = nullptr;
        RendererMaterialGL* material = nullptr;

        Id id;
        RenderContent* content = nullptr;
    };
}