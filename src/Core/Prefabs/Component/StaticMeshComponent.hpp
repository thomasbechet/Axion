#pragma once

/////////////////
//HEADERS
/////////////////
#include <Core/Export.hpp>
#include <Core/World/Entity/Component.hpp>

namespace ax
{
    struct AXION_CORE_API StaticMeshComponent : public Component
    {
    public:
        static std::string name(){return "StaticMesh";}

        void setMesh(std::string name) noexcept;

        TransformComponent& transform;

    private:
        std::shared_ptr<const Mesh> m_mesh;
    };
}