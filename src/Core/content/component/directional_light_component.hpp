#pragma once

#include <core/export.hpp>
#include <core/utility/types.hpp>
#include <core/utility/color.hpp>
#include <core/renderer/scene/renderer_directional_light.hpp>
#include <core/scene/component/component.hpp>
#include <core/content/component/transform_component.hpp>

namespace ax
{
    class AXION_CORE_API directional_light_component : public component
    {
    public:
        COMPONENT_IDENTIFIER("directional_light")
        COMPONENT_REQUIREMENTS(transform_component)
        
        directional_light_component(entity& entity, const json& json);
        directional_light_component(entity& entity);
        ~directional_light_component();

        void set_color(color3 color) noexcept;
        color3 get_color() const noexcept;

        transform_component& transform;
    
    private:
        renderer_directional_light_handle m_handle;
        renderer_directional_light_parameters m_parameters;
    };
}