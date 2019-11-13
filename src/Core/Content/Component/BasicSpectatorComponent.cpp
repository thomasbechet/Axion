#include <Core/Content/Component/BasicSpectatorComponent.hpp>

using namespace ax;

BasicSpectatorComponent::BasicSpectatorComponent(const Entity& entity, const Json& json) :
    transform(entity.getComponent<TransformComponent>()),
    camera(entity.getComponent<CameraComponent>())
{
    try
    {
        auto jNormalSpeed = json.find("normal_speed");
        if(jNormalSpeed != json.end() && jNormalSpeed->is_number_float())
            normalSpeed = jNormalSpeed->get<float>();

        auto jSlowSpeed = json.find("slow_speed");
        if(jSlowSpeed != json.end() && jSlowSpeed->is_number_float())
            slowSpeed = jSlowSpeed->get<float>();

        auto jFastSpeed = json.find("fast_speed");
        if(jFastSpeed != json.end() && jFastSpeed->is_number_float())
            fastSpeed = jFastSpeed->get<float>();

        auto jRollSpeed = json.find("roll_speed");
        if(jRollSpeed != json.end() && jRollSpeed->is_number_float())
            rollSpeed = jRollSpeed->get<float>();

        auto jRotationSensibility = json.find("rotation_sensibility");
        if(jRotationSensibility != json.end() && jRotationSensibility->is_number_float())
            rotationSensibility = jRotationSensibility->get<float>();

        auto jZoomSpeed = json.find("zoom_speed");
        if(jZoomSpeed != json.end() && jZoomSpeed->is_number_float())
            zoomSpeed = jZoomSpeed->get<float>();

        auto jFreeMode = json.find("free_mode");
        if(jFreeMode != json.end() && jFreeMode->is_boolean())
            freeMode = jFreeMode->get<bool>();
    }
    catch(...) {}
}
BasicSpectatorComponent::BasicSpectatorComponent(const Entity& entity) :
    transform(entity.getComponent<TransformComponent>()),
    camera(entity.getComponent<CameraComponent>())
{
    
}