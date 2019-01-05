#pragma once

//////////////
//HEADERS
//////////////
#include <Core/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Math/Geometry/Shape.hpp>
#include <Core/World/Entity/Entity.hpp>
#include <Core/Prefab/Component/TransformComponent.hpp>
#include <Core/Asset/AssetReference.hpp>
#include <Core/Asset/Material.hpp>

namespace ax
{
    struct AXION_CORE_API UVSphereComponent : public Component
    {
    public:
        static std::string name(){return "UVSphere";}
        
        UVSphereComponent(const Entity& entity);
        ~UVSphereComponent();

        TransformComponent& transform;

    private:
        void generate() noexcept;

        float m_radius = 1.0f;
        unsigned m_UN = 10;
        unsigned m_VN = 10;
        bool m_smooth = false;

        Id m_staticmesh;
        Id m_mesh;
        AssetReference<Material> m_material;
    };
}