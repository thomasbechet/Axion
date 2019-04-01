#pragma once

#include <GLFW/Export.hpp>
#include <Core/Input/Input.hpp>

#include <memory>

class GLFWwindow;

namespace ax
{
    class AXION_GLFW_API InputGLFW : public Input
    {
    public:
        friend class WrapperInputGLFW;

        bool isButtonPressed(Keyboard key) const noexcept override;
        bool isButtonPressed(Mouse::Button button) const noexcept override;
        bool isButtonPressed(Gamepad::Button button) const noexcept override;
        bool isButtonReleased(Keyboard key) const noexcept override;
        bool isButtonReleased(Mouse::Button button) const noexcept override;
        bool isButtonReleased(Gamepad::Button button) const noexcept override;
        void setCursorMode(CursorMode mode) noexcept override;
        CursorMode getCursorMode() const noexcept override;
        Vector2f getMousePosition() const noexcept override;
        Vector2f getMouseMotion() const noexcept override;
        Vector2f getMouseScroll() const noexcept override;
        float getGamepadAxis(Gamepad::Axis axis) const noexcept override;

        void cursorPositionCallback(double xpos, double ypos) noexcept;
        void cursorScrollCallback(double xaxis, double yaxis) noexcept;

        void initialize() noexcept override;
        void terminate() noexcept override;
        void update() noexcept override;

    private:
        GLFWwindow* m_window = nullptr;

        Vector2f m_mousePosition = Vector2f(0, 0);
        Vector2f m_mouseOldPosition = Vector2f(0, 0);
        Vector2f m_mouseMotion = Vector2f(0, 0);

        Vector2f m_mouseScroll = Vector2f(0, 0);
        bool m_mouseScrollStay = false;

        CursorMode m_cursorMode = CursorMode::Normal;
    };
}