#pragma once

//////////////
//HEADERS
//////////////
#include <Core/Export.hpp>
#include <Core/World/Entity/Entity.hpp>
#include <Core/World/Component/Component.hpp>
#include <Core/Prefabs/Component/TransformComponent.hpp>

namespace ax
{
    struct AXION_CORE_API BasicControllerComponent : public Component
    {
        static std::string name(){return "BasicController";}

        BasicControllerComponent(const Entity& entity);

        TransformComponent& transform;
        float speed = 10.0f; // m/s
    };
}