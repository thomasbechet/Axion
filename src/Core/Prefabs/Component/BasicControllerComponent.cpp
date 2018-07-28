#include <Core/Prefabs/Component/BasicControllerComponent.hpp>

using namespace ax;

BasicControllerComponent::BasicControllerComponent(const Entity& entity) :
    transform(entity.getComponent<TransformComponent>())
{
    
}