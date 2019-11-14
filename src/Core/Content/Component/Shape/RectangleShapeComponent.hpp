#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Utility/Reference.hpp>
#include <Core/Math/Geometry/Rectangle.hpp>
#include <Core/Scene/Entity/Entity.hpp>
#include <Core/Content/Component/TransformComponent.hpp>
#include <Core/Content/Asset/Material.hpp>
#include <Core/Renderer/Scene/RendererStaticmesh.hpp>
#include <Core/Renderer/Asset/RendererMesh.hpp>

namespace ax
{
    struct AXION_CORE_API RectangleShapeComponent : public Rectangle, public Component
    {
    public:
        COMPONENT_IDENTIFIER("rectangle_shape")
        COMPONENT_REQUIREMENT(TransformComponent)
        
        RectangleShapeComponent(const Entity& entity, const Json& json);
        RectangleShapeComponent(const Entity& entity,
            float xMin = -0.5f, float xMax = 0.5f,
            float yMin = -0.5f, float yMax = 0.5f,
            float zMin = -0.5f, float zMax = 0.5f,
            bool smooth = true,
            float factor = 1.0f
        );
        ~RectangleShapeComponent();

        void setMaterial(std::nullptr_t) noexcept;
        void setMaterial(const std::string& name) noexcept;
        void setMaterial(Reference<Material> material) noexcept;

        void setCoordinateFactor(float factor) noexcept;

        void generate() noexcept;

        TransformComponent& transform;

    private:
        float parseNumber(const Json& json, const std::string& name) noexcept;

        float m_coordinateFactor = 1.0f;

        RendererStaticmeshHandle m_staticmesh;
        RendererMeshHandle m_mesh;
        Reference<Material> m_material;
    };
}