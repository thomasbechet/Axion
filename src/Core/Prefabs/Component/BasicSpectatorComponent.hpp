#pragma once

//////////////
//HEADERS
//////////////
#include <Core/Export.hpp>
#include <Core/World/Entity/Entity.hpp>
#include <Core/World/Component/Component.hpp>
#include <Core/Prefabs/Component/TransformComponent.hpp>
#include <Core/Prefabs/Component/CameraComponent.hpp>

namespace ax
{
    struct AXION_CORE_API BasicSpectatorComponent : public Component
    {
        static std::string name(){return "SpectatorController";}

        BasicSpectatorComponent(const Entity& entity);

        TransformComponent& transform;
        CameraComponent& camera;

        float speed = 10.0f; // m/s
        float rotationSpeed = 50.0f; //deg/s
        float zoomDelta = 5.0f;
    };
}