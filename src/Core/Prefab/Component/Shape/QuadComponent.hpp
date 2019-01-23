#pragma once

//////////////
//HEADERS
//////////////
#include <Core/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Math/Geometry/Quad.hpp>
#include <Core/World/Entity/Entity.hpp>
#include <Core/Prefab/Component/TransformComponent.hpp>
#include <Core/Asset/AssetReference.hpp>
#include <Core/Asset/Material.hpp>

namespace ax
{
    struct AXION_CORE_API QuadComponent : public Quad, public Component
    {
    public:
        static std::string name(){return "Quad";}
        
        QuadComponent(const Entity& entity, float x = 1.0f, float y = 1.0f, float factor = 1.0f);
        ~QuadComponent();

        void setMaterial(std::nullptr_t) noexcept;
        void setMaterial(std::string name) noexcept;
        void setMaterial(AssetReference<Material> material) noexcept;

        void setCoordinateFactor(float factor) noexcept;

        void generate() noexcept;

        TransformComponent& transform;

    private:
        float m_coordinateFactor = 1.0f;

        Id m_staticmesh;
        Id m_mesh;
        AssetReference<Material> m_material;
    };
}