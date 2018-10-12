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

namespace ax
{
    struct AXION_CORE_API StaticMeshComponent : public Component
    {
    public:
        static std::string name(){return "StaticMesh";}

        StaticMeshComponent(const Entity& entity);
        ~StaticMeshComponent();

        void setMesh(std::string name) noexcept;
        void setMesh(AssetReference<Mesh>& mesh) noexcept;

        TransformComponent& transform;

    private:
        Id m_handle;
        AssetReference<Mesh> m_mesh;
    };
}