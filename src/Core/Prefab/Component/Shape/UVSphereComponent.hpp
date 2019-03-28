#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Math/Geometry/UVSphere.hpp>
#include <Core/World/Entity/Entity.hpp>
#include <Core/Prefab/Component/TransformComponent.hpp>
#include <Core/Asset/AssetReference.hpp>
#include <Core/Asset/Material.hpp>

namespace ax
{
    struct AXION_CORE_API UVSphereComponent : public UVSphere, public Component
    {
    public:
        static const std::string name;
        
        UVSphereComponent(const Entity& entity,
            float radius = 1.0f,
            unsigned slice = 30,
            unsigned stack = 30,
            bool smooth = true,
            float factor = 1.0f
        );
        ~UVSphereComponent();

        void setMaterial(std::nullptr_t) noexcept;
        void setMaterial(std::string name) noexcept;
        void setMaterial(AssetReference<Material> material) noexcept;

        void setSmooth(bool smooth) noexcept;
        void setCoordinateFactor(float factor) noexcept;

        void generate() noexcept;

        TransformComponent& transform;

    private:
        bool m_smooth = false;
        float m_coordinateFactor = 1.0f;

        Id m_staticmesh;
        Id m_mesh;
        AssetReference<Material> m_material;
    };
}