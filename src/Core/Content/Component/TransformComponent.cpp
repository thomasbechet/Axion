#include <Core/Content/Component/TransformComponent.hpp>

#include <Core/Utility/JsonUtility.hpp>

using namespace ax;

TransformComponent::TransformComponent(const Entity& entity, const Json& json)
{
    setTranslation(JsonUtility::readVector3f(json, "translation"));
    setRotation(JsonUtility::readQuaternionf(json, "rotation"));
    setScale(JsonUtility::readVector3f(json, "scale"));
}
TransformComponent::TransformComponent(const Entity& entity, Vector3f position, Quaternionf rotation, Vector3f scale) 
    : Transform(position, rotation, scale)
{
    
}

void TransformComponent::attachTo(const Entity& entity) noexcept
{
    setParent(&entity.getComponent<TransformComponent>());
}