#pragma once

#include <core/export.hpp>
#include <core/scene/system/system.hpp>
#include <core/scene/component/component_list.hpp>
#include <core/content/component/basic_spectator_component.hpp>
#include <core/input/button.hpp>
#include <core/input/axis.hpp>
#include <core/utility/macro.hpp>

namespace ax
{
    class AXION_CORE_API basic_spectator_system : public system
    {
    public:
        SYSTEM_IDENTIFIER("basic_spectator")

        void on_initialize() override;
        void on_update() override;
        void on_terminate() override;

        void add(basic_spectator_component& component) noexcept;

    private:
        button* m_forward = nullptr;
        button* m_backward = nullptr;
        button* m_left = nullptr;
        button* m_right = nullptr;
        button* m_up = nullptr;
        button* m_down = nullptr;
        button* m_rotate_left = nullptr;
        button* m_rotate_right = nullptr;
        button* m_slow_mode = nullptr;
        button* m_fast_mode = nullptr;
        button* m_change_mode = nullptr;
        button* m_next_camera = nullptr;
        axis* m_look_x = nullptr;
        axis* m_look_y = nullptr;
        axis* m_zoom = nullptr;

        std::vector<basic_spectator_component*> m_components;
        unsigned m_active = 0;
    };
}