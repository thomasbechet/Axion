#pragma once

#include <core/export.hpp>
#include <core/scene/system/system.hpp>
#include <core/input/button.hpp>
#include <core/utility/macro.hpp>

#include <string>

namespace ax
{
    class AXION_CORE_API basic_window_system : public system
    {
    public:
        SYSTEM_IDENTIFIER("basic_window")

        void on_initialize() override;
        void on_update() override;
        void on_terminate() override;

    private:
        button* m_fullscreen_button = nullptr;
        button* m_borderless_button = nullptr;
        button* m_close_button = nullptr;
        button* m_vsync_button = nullptr;
    };
}