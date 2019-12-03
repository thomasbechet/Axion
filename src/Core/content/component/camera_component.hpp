#pragma once

#include <core/export.hpp>
#include <core/utility/types.hpp>
#include <core/scene/entity/entity.hpp>
#include <core/content/component/transform_component.hpp>
#include <core/renderer/scene/renderer_camera.hpp>
#include <core/renderer/gui/renderer_gui_viewport.hpp>

namespace ax
{
    class AXION_CORE_API camera_component : public component
    {
    public:
        COMPONENT_IDENTIFIER("camera")
        COMPONENT_REQUIREMENTS(transform_component) 
          
        camera_component(entity& entity, const json& json);
        camera_component(entity& entity);
        ~camera_component();

        void bind_default_viewport() noexcept;
        void bind_viewport(renderer_gui_viewport_handle viewport) noexcept;

        void set_fov(float fov) noexcept;
        float get_fov() const noexcept;
        void set_far_plane(float far) noexcept;
        float get_far_plane() const noexcept;
        void set_near_plane(float near) noexcept;
        float get_near_plane() const noexcept;

        transform_component& transform;

    private:
        void update_renderer_parameters() noexcept;
        
        renderer_camera_handle m_handle;
        renderer_camera_parameters m_parameters;
    };
}