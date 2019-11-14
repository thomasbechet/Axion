#include <Core/Content/Component/TransformComponent.hpp>

using namespace ax;

TransformComponent::TransformComponent(const Entity& entity, const Json& json)
{
    try
    {
        auto jTranslation = json.find("translation");
        if(jTranslation != json.end() && jTranslation->is_array())
            setTranslation(Vector3f(*jTranslation));

        auto jRotation = json.find("rotation");
        if(jRotation != json.end() && jRotation->is_array())
            setRotation(Quaternionf(*jRotation));

        auto jScale = json.find("scale");
        if(jScale != json.end() && jScale->is_array())
            setScale(Vector3f(*jScale));
    }
    catch(...) {}
}
TransformComponent::TransformComponent(const Entity& entity, Vector3f position, Quaternionf rotation, Vector3f scale) 
    : Transform(position, rotation, scale)
{
    
}

void TransformComponent::attachTo(const Entity& entity) noexcept
{
    setParent(&entity.getComponent<TransformComponent>());
}