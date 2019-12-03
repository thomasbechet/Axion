#pragma once

#include <core/export.hpp>
#include <core/scene/entity/entity.hpp>
#include <core/scene/component/component.hpp>
#include <core/content/component/transform_component.hpp>
#include <core/content/component/camera_component.hpp>

namespace ax
{
    class AXION_CORE_API basic_spectator_component : public component
    {
    public:
        COMPONENT_IDENTIFIER("basic_spectator")
        COMPONENT_REQUIREMENTS(transform_component, camera_component)
        
        basic_spectator_component(entity& entity, const json& json);
        basic_spectator_component(entity& entity);

        transform_component& transform;
        camera_component& camera;

        float normal_speed = 20.0f; // m/s
        float slow_speed = 2.0f; // m/s
        float fast_speed = 500.0f; // m/s
        float roll_speed = 90.0f; //deg/s
        float rotation_sensibility = 0.3f;
        float zoom_speed = 5.0f;

        bool free_mode = false;

        float yaw = 0.0f;
        float pitch = 0.0f;
    };
}