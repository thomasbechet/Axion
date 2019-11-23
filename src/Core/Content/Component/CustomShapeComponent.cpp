#include <Core/Content/Component/CustomShapeComponent.hpp>

using namespace ax;

CustomShapeComponent::CustomShapeComponent(Entity& entity, const Json& json) :
    transform(entity.getComponent<TransformComponent>())
{

}
CustomShapeComponent::CustomShapeComponent(Entity& entity) :
    transform(entity.getComponent<TransformComponent>())
{

}
CustomShapeComponent::~CustomShapeComponent()
{

}