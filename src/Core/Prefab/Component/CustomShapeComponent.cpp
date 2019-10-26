#include <Core/Prefab/Component/CustomShapeComponent.hpp>

using namespace ax;

const std::string CustomShapeComponent::type = "CustomShape";

CustomShapeComponent::CustomShapeComponent(const Entity& entity) :
    transform(entity.getComponent<TransformComponent>())
{

}
CustomShapeComponent::~CustomShapeComponent()
{

}