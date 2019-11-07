#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Utility/Reference.hpp>
#include <Core/Math/Geometry/UVSphere.hpp>
#include <Core/Scene/Entity/Entity.hpp>
#include <Core/Prefab/Component/TransformComponent.hpp>
#include <Core/Asset/Asset/Material.hpp>
#include <Core/Renderer/Scene/RendererStaticmesh.hpp>
#include <Core/Renderer/Asset/RendererMesh.hpp>

namespace ax
{
    struct AXION_CORE_API UVSphereShapeComponent : public UVSphere, public Component
    {
    public:
        COMPONENT_IDENTIFIER("uv_sphere_shape")
        COMPONENT_REQUIREMENT(TransformComponent)

        UVSphereShapeComponent(const Entity& entity, const Json& json);
        UVSphereShapeComponent(const Entity& entity,
            float radius = 1.0f,
            unsigned slice = 30,
            unsigned stack = 30,
            bool smooth = true,
            float factor = 1.0f
        );
        ~UVSphereShapeComponent();

        void setMaterial(std::nullptr_t) noexcept;
        void setMaterial(const std::string& name) noexcept;
        void setMaterial(Reference<Material> material) noexcept;

        void setSmooth(bool smooth) noexcept;
        void setCoordinateFactor(float factor) noexcept;

        void generate() noexcept;

        TransformComponent& transform;

    private:
        bool m_smooth = false;
        float m_coordinateFactor = 1.0f;

        RendererStaticmeshHandle m_staticmesh;
        RendererMeshHandle m_mesh;
        Reference<Material> m_material;
    };
}