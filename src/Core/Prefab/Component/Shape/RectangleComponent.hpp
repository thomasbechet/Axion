#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Math/Geometry/Rectangle.hpp>
#include <Core/Scene/Entity/Entity.hpp>
#include <Core/Prefab/Component/TransformComponent.hpp>
#include <Core/Asset/AssetReference.hpp>
#include <Core/Asset/Asset/Material.hpp>
#include <Core/Renderer/Scene/RendererStaticmesh.hpp>
#include <Core/Renderer/Asset/RendererMesh.hpp>

namespace ax
{
    struct AXION_CORE_API RectangleComponent : public Rectangle, public Component
    {
    public:
        static const std::string type;
        
        RectangleComponent(const Entity& entity,
            float xMin = -0.5f, float xMax = 0.5f,
            float yMin = -0.5f, float yMax = 0.5f,
            float zMin = -0.5f, float zMax = 0.5f,
            bool smooth = true,
            float factor = 1.0f
        );
        ~RectangleComponent();

        void setMaterial(std::nullptr_t) noexcept;
        void setMaterial(std::string name) noexcept;
        void setMaterial(AssetReference<Material> material) noexcept;

        void setCoordinateFactor(float factor) noexcept;

        void generate() noexcept;

        TransformComponent& transform;

    private:
        float m_coordinateFactor = 1.0f;

        RendererStaticmeshHandle m_staticmesh;
        RendererMeshHandle m_mesh;
        AssetReference<Material> m_material;
    };
}