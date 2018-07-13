#pragma once

//////////////
//HEADERS
//////////////
#include <GLFW/Export.hpp>
#include <Core/Window/Window.hpp>

//Forward declaration
class GLFWwindow;

namespace ax
{
    class AXION_GLFW_API WindowGLFW : public Window
    {
    public:
        friend class WrapperWindowGLFW;

    protected:
        void initialize() noexcept override;
        void terminate() noexcept override;
        void update() noexcept override;

        void swapBuffers() noexcept override;

    public:
        bool requestGLContext() noexcept override;
        bool requestDXContext() noexcept override;
        bool requestVKContext() noexcept override;

        bool shouldClose() noexcept override;

        void setTitle(std::string title) noexcept override;
        std::string getTitle() const noexcept override;
        void setSize(Vector2u size) noexcept override;
        Vector2u getSize() const noexcept override;
        void setPosition(Vector2i position) noexcept override;
        Vector2i getPosition() const noexcept override;
        void setMode(WindowMode mode) noexcept override;
        WindowMode getMode() noexcept override;
        void setVerticalSync(bool toggle) noexcept override;
        bool getVerticalSync() const noexcept override;

    public:
        GLFWwindow* rawWindow() const noexcept;

    private:
        void windowPosCallback(int xpos, int ypos) noexcept;
        void windowSizeCallback(int width, int height) noexcept;

    private:
        GLFWwindow* m_window = nullptr;
        std::string m_title = "";
        WindowMode m_mode = WindowMode::Windowed;
        bool m_verticalSync = true;
        Vector2u m_size = Vector2u(0, 0);
        Vector2i m_position = Vector2i(0, 0);
    };
}