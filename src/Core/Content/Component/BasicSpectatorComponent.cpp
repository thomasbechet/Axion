#include <Core/Content/Component/BasicSpectatorComponent.hpp>

#include <Core/Utility/JsonUtility.hpp>

using namespace ax;

BasicSpectatorComponent::BasicSpectatorComponent(const Entity& entity, const Json& json) :
    transform(entity.getComponent<TransformComponent>()),
    camera(entity.getComponent<CameraComponent>())
{
    normalSpeed = JsonUtility::readFloat(json, "normal_speed", normalSpeed);
    slowSpeed = JsonUtility::readFloat(json, "slow_speed", slowSpeed);
    fastSpeed = JsonUtility::readFloat(json, "fast_speed", fastSpeed);
    rollSpeed = JsonUtility::readFloat(json, "roll_speed", rollSpeed);
    rotationSensibility = JsonUtility::readFloat(json, "rotation_sensibility", rotationSensibility);
    zoomSpeed = JsonUtility::readFloat(json, "zoom_speed", zoomSpeed);
    freeMode = JsonUtility::readBoolean(json, "free_mode", freeMode);
}
BasicSpectatorComponent::BasicSpectatorComponent(const Entity& entity) :
    transform(entity.getComponent<TransformComponent>()),
    camera(entity.getComponent<CameraComponent>())
{
    
}