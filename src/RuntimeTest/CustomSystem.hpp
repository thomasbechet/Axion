#pragma once

#include <Core/Scene/System/System.hpp>
#include <Core/Utility/Macro.hpp>
#include <Core/Scene/Entity/Entity.ipp>
#include <Core/Utility/Json.hpp>
#include <Core/Content/Component/TransformComponent.hpp>

class RotationComponent : public ax::Component
{
public:
    COMPONENT_IDENTIFIER("rotation")
    COMPONENT_REQUIREMENTS(ax::TransformComponent) 

    RotationComponent(ax::Entity& entity, const ax::Json& json)
        : RotationComponent(entity)
    {

    }
    RotationComponent(ax::Entity& entity) :
        transform(entity.getComponent<ax::TransformComponent>())
    {

    }

    ax::TransformComponent& transform;
};

class RotationSystem : public ax::System
{
public:
    SYSTEM_IDENTIFIER("rotation")

    void onUpdate() override
    {
        for(auto& rot : ax::Engine::scene().component.list<RotationComponent>())
        {
            rot.transform.rotate(ax::Math::radians(10.0f) * ax::Engine::context().getDeltaTime().asSeconds(),
                ax::Vector3f::up);
        }
    }
};