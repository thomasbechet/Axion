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

        Id createLayout() noexcept override {}
        void destroyLayout(Id layout) noexcept override {}

        Id createButton(Id layout) noexcept override {}
        void destroyButton(Id button) noexcept override {}
        Id createText(Id layout) noexcept override {}
        void destroyText(Id button) noexcept override {}
    };
}