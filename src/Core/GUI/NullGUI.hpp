#pragma once

#include <Core/Export.hpp>
#include <Core/GUI/GUI.hpp>

namespace ax
{
    class AXION_CORE_API NullGUI : public GUI
    {
    protected:
        void initialize() noexcept override {}
        void terminate() noexcept override {}
        void update() noexcept override {}
        void render() noexcept override {}
    };
}