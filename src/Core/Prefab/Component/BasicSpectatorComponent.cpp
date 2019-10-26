#include <Core/Prefab/Component/BasicSpectatorComponent.hpp>

using namespace ax;

const std::string BasicSpectatorComponent::type = "BasicSpectator";

BasicSpectatorComponent::BasicSpectatorComponent(const Entity& entity) :
    transform(entity.getComponent<TransformComponent>()),
    camera(entity.getComponent<CameraComponent>())
{
    
}