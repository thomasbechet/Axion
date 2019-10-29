#include <Core/Prefab/Component/TransformComponent.hpp>

using namespace ax;

TransformComponent::TransformComponent(const Entity& entity, const Json& json)
{
    try
    {
        std::vector<float> translation = json["translation"].get<std::vector<float>>();
        setTranslation(translation.at(0), translation.at(1), translation.at(2));

        std::vector<float> rotation = json["rotation"].get<std::vector<float>>();
        //TODO

        std::vector<float> scale = json["scale"].get<std::vector<float>>();
        setScale(scale.at(0), scale.at(1), scale.at(2));
    }
    catch(const std::exception& e)
    {
        //Do nothing
    }
}
TransformComponent::TransformComponent(const Entity& entity, Vector3f position, Quaternionf rotation, Vector3f scale) 
    : Transform(position, rotation, scale)
{
    
}

void TransformComponent::attachTo(const Entity& entity) noexcept
{
    setParent(&entity.getComponent<TransformComponent>());
}