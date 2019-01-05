#include <Core/Prefab/Component/CustomShapeComponent.hpp>

using namespace ax;

CustomShapeComponent::CustomShapeComponent(const Entity& entity) :
    transform(entity.getComponent<TransformComponent>())
{

}
CustomShapeComponent::~CustomShapeComponent()
{

}