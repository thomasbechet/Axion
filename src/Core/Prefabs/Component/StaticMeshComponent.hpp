#pragma once

/////////////////
//HEADERS
/////////////////
#include <Core/Export.hpp>
#include <Core/World/Entity/Component.hpp>

namespace ax
{
    class AXION_CORE_API StaticMeshComponent : public Component
    {
    public:
        static std::string name(){return "StaticMesh";}
        void load(const Entity& e) noexcept;
        void unload() noexcept;

    private:

    };
}