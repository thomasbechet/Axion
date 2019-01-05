#include <Core/Prefab/Component/BasicSpectatorComponent.hpp>

using namespace ax;

BasicSpectatorComponent::BasicSpectatorComponent(const Entity& entity) :
    transform(entity.getComponent<TransformComponent>()),
    camera(entity.getComponent<CameraComponent>())
{
    
}