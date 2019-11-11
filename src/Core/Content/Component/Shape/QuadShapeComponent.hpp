#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Utility/Reference.hpp>
#include <Core/Math/Geometry/Quad.hpp>
#include <Core/Scene/Entity/Entity.hpp>
#include <Core/Content/Component/TransformComponent.hpp>
#include <Core/Content/Asset/Material.hpp>
#include <Core/Renderer/Scene/RendererStaticmesh.hpp>
#include <Core/Renderer/Asset/RendererMesh.hpp>

namespace ax
{
    struct AXION_CORE_API QuadShapeComponent : public Quad, public Component
    {
    public:
        COMPONENT_IDENTIFIER("quad_shape")
        COMPONENT_REQUIREMENT(TransformComponent)
        
        QuadShapeComponent(const Entity& entity, const Json& json);
        QuadShapeComponent(const Entity& entity, float x = 1.0f, float y = 1.0f, float factor = 1.0f);
        ~QuadShapeComponent();

        void setMaterial(std::nullptr_t) noexcept;
        void setMaterial(const std::string& name) noexcept;
        void setMaterial(Reference<Material> material) noexcept;

        void setCoordinateFactor(float factor) noexcept;

        void generate() noexcept;

        TransformComponent& transform;

    private:
        float m_coordinateFactor = 1.0f;

        RendererStaticmeshHandle m_staticmesh;
        RendererMeshHandle m_mesh;
        Reference<Material> m_material;
    };
}