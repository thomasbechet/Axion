#include <Core/Prefab/Component/TransformComponent.hpp>

using namespace ax;

TransformComponent::TransformComponent(Vector3f position, Quaternionf rotation, Vector3f scale) 
    : Transform(position, rotation, scale)
{
    
}

void TransformComponent::attachTo(const Entity& entity) noexcept
{
    setParent(&entity.getComponent<TransformComponent>());
}