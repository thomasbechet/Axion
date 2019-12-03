#include <core/content/component/basic_spectator_component.hpp>

#include <core/utility/json_utility.hpp>

using namespace ax;

basic_spectator_component::basic_spectator_component(entity& entity, const json& json) :
    transform(entity.get_component<transform_component>()),
    camera(entity.get_component<camera_component>())
{
    normal_speed = json_utility::read_float(json, "normal_speed", normal_speed);
    slow_speed = json_utility::read_float(json, "slow_speed", slow_speed);
    fast_speed = json_utility::read_float(json, "fast_speed", fast_speed);
    roll_speed = json_utility::read_float(json, "roll_speed", roll_speed);
    rotation_sensibility = json_utility::read_float(json, "rotation_sensibility", rotation_sensibility);
    zoom_speed = json_utility::read_float(json, "zoom_speed", zoom_speed);
    free_mode = json_utility::read_boolean(json, "free_mode", free_mode);
}
basic_spectator_component:basic_spectator_component(entity& entity) :
    transform(entity.get_component<_transform_component>()),
    camera(entity.get_component<camera_component>())
{
    
}