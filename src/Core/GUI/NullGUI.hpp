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

        Id createLayout() noexcept override {return 0;}
        void destroyLayout(Id layout) noexcept override {}

        Id createButton(Id layout, GUIButton& button) noexcept override {return 0;}
        void destroyButton(Id button) noexcept override {}
        Id createText(Id layout, GUIText& text) noexcept override {return 0;}
        void destroyText(Id button) noexcept override {}
    };
}