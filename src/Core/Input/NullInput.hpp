#pragma once

////////////////
//HEADERS
////////////////
#include <Core/Export.hpp>
#include <Core/Input/Input.hpp>

#include <memory>

namespace ax
{
    class AXION_CORE_API NullInput : public Input
    {
    public:
        bool isButtonPressed(Keyboard key) const noexcept override {return false;}
        bool isButtonPressed(Mouse::Button button) const noexcept override {return false;}
        bool isButtonPressed(Gamepad::Button button) const noexcept override {return false;}
        bool isButtonReleased(Keyboard key) const noexcept override {return false;};
        bool isButtonReleased(Mouse::Button button) const noexcept override {return false;}
        bool isButtonReleased(Gamepad::Button button) const noexcept override {return false;}
        virtual void setCursorMode(CursorMode mode) noexcept override {}
        virtual CursorMode getCursorMode() const noexcept override {return CursorMode::Normal;}
        Vector2f getMousePosition() const noexcept override {return Vector2f(0, 0);}
        Vector2f getMouseMotion() const noexcept override {return Vector2f(0, 0);}
        void resetMouseMotion() noexcept override {}
        Vector2f getMouseScroll() const noexcept override {return Vector2f(0, 0);}
        virtual float getGamepadAxis(Gamepad::Axis axis) const noexcept override {return 0.0f;}

    protected:
        void initialize() noexcept override {}
        void terminate() noexcept override {}
        void update() noexcept override {}
    };
}