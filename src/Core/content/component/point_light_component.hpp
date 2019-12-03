#pragma once

#include <core/export.hpp>
#include <core/utility/types.hpp>
#include <core/utility/color.hpp>
#include <core/renderer/scene/renderer_point_light.hpp>
#include <core/scene/component/component.hpp>
#include <core/content/component/transform_component.hpp>

namespace ax
{
    class AXION_CORE_API point_light_component : public component
    {
    public:
        COMPONENT_IDENTIFIER("point_light")
        COMPONENT_REQUIREMENTS(transform_component)
        
        point_light_component(entity& entity, const json& json);
        point_light_component(entity& entity);
        ~point_light_component();

        void set_radius(float radius) noexcept;
        float get_radius() const noexcept;

        void set_color(color3 color) noexcept;
        color3 get_color() const noexcept;
  
        transform_component& transform;
    
    private:
        renderer_point_light_handle m_handle;
        renderer_point_light_parameters m_parameters;
    };
}