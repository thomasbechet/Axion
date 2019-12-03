#pragma once

#include <core/export.hpp>
#include <core/scene/system/system.hpp>
#include <core/input/button.hpp>
#include <core/utility/macro.hpp>

#include <string>

namespace ax
{
    class AXION_CORE_API render_mode_system : public system
    {
    public:
        SYSTEM_IDENTIFIER("render_mode")

        void on_initialize() override;
        void on_update() override;
        void on_terminate() override;

    private:
        button* m_default_mode_button = nullptr;
        button* m_wireframe_mode_button = nullptr;
        button* m_debug_mode_button = nullptr;
    };
}