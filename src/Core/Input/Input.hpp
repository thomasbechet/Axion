#pragma once

//////////////////
//HEADERS
//////////////////
#include <Core/Export.hpp>
#include <Core/Input/Button.hpp>
#include <Core/Input/Axis.hpp>
#include <Core/Input/Keyboard.hpp>
#include <Core/Input/Mouse.hpp>
#include <Core/Input/Gamepad.hpp>
#include <Core/Math/Vector.hpp>

#include <unordered_map>

namespace ax
{
    enum CursorMode
    {
        Normal,
        Hidden,
        Disable
    };

    class AXION_CORE_API Input
    {
    public:
        friend class GameContext;
        virtual ~Input(){}

        virtual bool isButtonPressed(Keyboard key) const noexcept = 0;
        virtual bool isButtonPressed(Mouse::Button button) const noexcept = 0;
        virtual bool isButtonPressed(Gamepad::Button button) const noexcept = 0;
        virtual bool isButtonReleased(Keyboard key) const noexcept = 0;
        virtual bool isButtonReleased(Mouse::Button button) const noexcept = 0;
        virtual bool isButtonReleased(Gamepad::Button button) const noexcept = 0;
        virtual void setCursorMode(CursorMode mode) noexcept = 0;
        virtual CursorMode getCursorMode() const noexcept = 0;
        virtual Vector2f getMousePosition() const noexcept = 0;
        virtual Vector2f getMouseMotion() const noexcept = 0;
        virtual Vector2f getMouseScroll() const noexcept = 0;
        virtual float getGamepadAxis(Gamepad::Axis axis) const noexcept = 0;
        

    protected:
        virtual void initialize() noexcept = 0;
        virtual void terminate() noexcept = 0;
        virtual void update() noexcept = 0;

    private:
        void updateInputs() noexcept;

    public:
        Button& addButton(std::string name) noexcept;
        Button& getButton(std::string name) noexcept;
        void removeButton(std::string name) noexcept;

        Axis& addAxis(std::string name) noexcept;
        Axis& getAxis(std::string name) noexcept;
        void removeAxis(std::string name) noexcept;

    private:
        std::unordered_map<std::string, Button> m_buttons;
        std::unordered_map<std::string, Axis> m_axis;
    };
}