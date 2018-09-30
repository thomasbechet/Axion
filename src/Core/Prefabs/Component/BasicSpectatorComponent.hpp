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
    public:
        static std::string name(){return "SpectatorController";}

        BasicSpectatorComponent(const Entity& entity);

        TransformComponent& transform;
        CameraComponent& camera;

        float normalSpeed = 10.0f; // m/s
        float slowSpeed = 2.0f; // m/s
        float fastSpeed = 30.0f; // m/s
        float rollSpeed = 90.0f; //deg/s
        float rotationSensibility = 0.3f;
        float zoomSpeed = 5.0f;

        bool freeMode = false;

        float yaw = 0.0f;
        float pitch = 0.0f;
    };
}