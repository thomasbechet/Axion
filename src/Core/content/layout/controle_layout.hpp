#pragma once

#include <core/export.hpp>
#include <core/gui/gui_layout.hpp>
#include <core/gui/widget/gui_label.hpp>

namespace ax
{
    class AXION_CORE_API console_layout : public gui_layout
    {
    public:
        console_layout();

        void on_start() override;
        void on_stop() override;
        void on_update() override;
    };
}