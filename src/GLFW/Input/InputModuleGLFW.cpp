#include <GLFW/Input/InputModuleGLFW.hpp>

#include <Core/Engine/Engine.hpp>
#include <Core/Context/ContextModule.hpp>
#include <GLFW/Window/WindowModuleGLFW.hpp>
#include <GLFW/Input/WrapperInputModuleGLFW.hpp>

#include <GLFW/glfw3.h>

#include <functional>

using namespace ax;

static int glfw_keyboard_buttons[] = 
{
    GLFW_KEY_A,
    GLFW_KEY_B,
    GLFW_KEY_C,
    GLFW_KEY_D,
    GLFW_KEY_E,
    GLFW_KEY_F,
    GLFW_KEY_G,
    GLFW_KEY_H,
    GLFW_KEY_I,
    GLFW_KEY_J,
    GLFW_KEY_K,
    GLFW_KEY_L,
    GLFW_KEY_M,
    GLFW_KEY_N,
    GLFW_KEY_O,
    GLFW_KEY_P,
    GLFW_KEY_Q,
    GLFW_KEY_R,
    GLFW_KEY_S,
    GLFW_KEY_T,
    GLFW_KEY_U,
    GLFW_KEY_V,
    GLFW_KEY_W,
    GLFW_KEY_X,
    GLFW_KEY_Y,
    GLFW_KEY_Z,

    GLFW_KEY_F1,
    GLFW_KEY_F2,
    GLFW_KEY_F3,
    GLFW_KEY_F4,
    GLFW_KEY_F5,
    GLFW_KEY_F6,
    GLFW_KEY_F7,
    GLFW_KEY_F8,
    GLFW_KEY_F9,
    GLFW_KEY_F10,
    GLFW_KEY_F11,
    GLFW_KEY_F12,
    
    GLFW_KEY_0,
    GLFW_KEY_1,
    GLFW_KEY_2,
    GLFW_KEY_3,
    GLFW_KEY_4,
    GLFW_KEY_5,
    GLFW_KEY_6,
    GLFW_KEY_7,
    GLFW_KEY_8,
    GLFW_KEY_9,

    GLFW_KEY_ESCAPE,
    GLFW_KEY_SPACE,
    GLFW_KEY_ENTER,
    GLFW_KEY_TAB,
    GLFW_KEY_BACKSPACE,
    GLFW_KEY_LEFT_SHIFT,
    GLFW_KEY_LEFT_CONTROL
};

static int glfw_mouse_buttons[] = 
{
    GLFW_MOUSE_BUTTON_LEFT,
    GLFW_MOUSE_BUTTON_RIGHT,
    GLFW_MOUSE_BUTTON_MIDDLE,
    GLFW_MOUSE_BUTTON_1,
    GLFW_MOUSE_BUTTON_2,
    GLFW_MOUSE_BUTTON_3,
    GLFW_MOUSE_BUTTON_4,
    GLFW_MOUSE_BUTTON_5,
    GLFW_MOUSE_BUTTON_6
};

void InputModuleGLFW::initialize() noexcept
{
    if(Engine::context().config.getString("Window", "type", "none") != "glfw")
        Engine::interrupt("WindowGLFW is required by InputGLFW, please change window's type to 'glfw'");

    m_window = static_cast<WindowModuleGLFW&>(Engine::window()).rawWindow();

    double xpos, ypos;
    glfwGetCursorPos(m_window, &xpos, &ypos);
    m_mousePosition = Vector2f((float)xpos, (float)ypos);
    m_mouseOldPosition = m_mousePosition;

    std::string cursorMode = Engine::context().config.getString("Input", "default_cursor_mode", "normal");
    if(cursorMode == "normal")
        setCursorMode(CursorMode::Normal);
    else if(cursorMode == "hidden")
        setCursorMode(CursorMode::Hidden);
    else if(cursorMode == "disable")
        setCursorMode(CursorMode::Disable);

    WrapperInputModuleGLFW::setInput(this, m_window);
}
void InputModuleGLFW::terminate() noexcept
{

}
void InputModuleGLFW::update() noexcept
{
    m_mouseMotion = m_mousePosition - m_mouseOldPosition;
    m_mouseOldPosition = m_mousePosition;

    if(!m_mouseScrollStay) m_mouseScroll = Vector2f(0, 0);
    m_mouseScrollStay = false;
}

bool InputModuleGLFW::isButtonPressed(Keyboard key) const noexcept
{
    int state = glfwGetKey(m_window, glfw_keyboard_buttons[(unsigned)key]);
    if(state == GLFW_PRESS) return true;
    else return false;
}
bool InputModuleGLFW::isButtonPressed(Mouse::Button button) const noexcept
{
    int state = glfwGetMouseButton(m_window, glfw_mouse_buttons[(unsigned)button]);
    if(state == GLFW_PRESS) return true;
    else return false;
}
bool InputModuleGLFW::isButtonPressed(Gamepad::Button button) const noexcept
{
    return false;
}
bool InputModuleGLFW::isButtonReleased(Keyboard key) const noexcept
{
    int state = glfwGetKey(m_window, glfw_keyboard_buttons[(unsigned)key]);
    if(state == GLFW_RELEASE) return true;
    else return false;
}
bool InputModuleGLFW::isButtonReleased(Mouse::Button button) const noexcept
{
    int state = glfwGetMouseButton(m_window, glfw_mouse_buttons[(unsigned)button]);
    if(state == GLFW_RELEASE) return true;
    else return false;
}
bool InputModuleGLFW::isButtonReleased(Gamepad::Button button) const noexcept
{
    return false;
}
void InputModuleGLFW::setCursorMode(CursorMode mode) noexcept
{
    switch(mode)
    {
        case CursorMode::Normal:
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        break;
        case CursorMode::Hidden:
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        break;
        case CursorMode::Disable:
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            if(glfwRawMouseMotionSupported())
                glfwSetInputMode(m_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
        break;
    }
    
}
CursorMode InputModuleGLFW::getCursorMode() const noexcept
{
    return m_cursorMode;
}
Vector2f InputModuleGLFW::getMousePosition() const noexcept
{
    return m_mousePosition;
}   
Vector2f InputModuleGLFW::getMouseMotion() const noexcept
{
    return m_mouseMotion;
}
Vector2f InputModuleGLFW::getMouseScroll() const noexcept
{
    return m_mouseScroll;
}
float InputModuleGLFW::getGamepadAxis(Gamepad::Axis axis) const noexcept
{
    return 0.0f;
}

void InputModuleGLFW::cursorPositionCallback(double xpos, double ypos) noexcept
{
    m_mousePosition = Vector2f((float)xpos, (float)ypos);
}
void InputModuleGLFW::cursorScrollCallback(double xaxis, double yaxis) noexcept
{
    m_mouseScroll = Vector2f((float)xaxis, (float)yaxis);
    m_mouseScrollStay = true;
}
