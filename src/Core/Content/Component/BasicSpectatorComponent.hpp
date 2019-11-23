#pragma once

#include <Core/Export.hpp>
#include <Core/Scene/Entity/Entity.hpp>
#include <Core/Scene/Component/Component.hpp>
#include <Core/Content/Component/TransformComponent.hpp>
#include <Core/Content/Component/CameraComponent.hpp>

namespace ax
{
    class AXION_CORE_API BasicSpectatorComponent : public Component
    {
    public:
        COMPONENT_IDENTIFIER("basic_spectator")
        COMPONENT_REQUIREMENTS(TransformComponent, CameraComponent)
        
        BasicSpectatorComponent(Entity& entity, const Json& json);
        BasicSpectatorComponent(Entity& entity);

        TransformComponent& transform;
        CameraComponent& camera;

        float normalSpeed = 20.0f; // m/s
        float slowSpeed = 2.0f; // m/s
        float fastSpeed = 500.0f; // m/s
        float rollSpeed = 90.0f; //deg/s
        float rotationSensibility = 0.3f;
        float zoomSpeed = 5.0f;

        bool freeMode = false;

        float yaw = 0.0f;
        float pitch = 0.0f;
    };
}