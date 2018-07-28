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
        static std::string name(){return "StaticMesh";}
    };
}