#pragma once

/////////////////
//HEADERS
/////////////////
#include <Core/Export.hpp>
#include <Core/World/Component/Component.hpp>
#include <Core/World/Entity/Entity.hpp>
#include <Core/Prefabs/Component/TransformComponent.hpp>
#include <Core/Assets/AssetReference.hpp>
#include <Core/Assets/Mesh.hpp>
#include <Core/Assets/Material.hpp>

namespace ax
{
    struct AXION_CORE_API MeshComponent : public Component
    {
    public:
        static std::string name(){return "Mesh";}

        MeshComponent(const Entity& entity);
        ~MeshComponent();

        void setMesh(std::nullptr_t) noexcept;
        void setMesh(std::string name) noexcept;
        void setMesh(AssetReference<Mesh> mesh) noexcept;
        void setMaterial(std::nullptr_t) noexcept;
        void setMaterial(std::string name) noexcept;
        void setMaterial(AssetReference<Material> material) noexcept;

        TransformComponent& transform;

    private:
        Id m_handle;
        AssetReference<Mesh> m_mesh;
        AssetReference<Material> m_material;
    };
}