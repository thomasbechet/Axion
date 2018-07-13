#pragma once

////////////////
//HEADERS
////////////////
#include <Core/Export.hpp>
#include <Core/Window/Window.hpp>

#include <memory>

namespace ax
{
    class AXION_CORE_API NullWindow : public Window
    {
    protected:
        void initialize() noexcept override {}
        void terminate() noexcept override {}
        void update() noexcept override {}

        void swapBuffers() noexcept override {}

    public:
        bool requestGLContext() noexcept override {return false;}
        bool requestDXContext() noexcept override {return false;}
        bool requestVKContext() noexcept override {return false;}

        bool shouldClose() noexcept override {return false;}

        void setTitle(std::string title) noexcept override {}
        std::string getTitle() const noexcept override {return "";}
        void setSize(Vector2u size) noexcept override {}
        Vector2u getSize() const noexcept override {return Vector2u(0, 0);}
        void setPosition(Vector2i position) noexcept override {}
        Vector2i getPosition() const noexcept override {return Vector2i(0, 0);}
        void setMode(WindowMode mode) noexcept override {}
        WindowMode getMode() noexcept override {return WindowMode::Fullscreen;}
        void setVerticalSync(bool toggle) noexcept override {}
        bool getVerticalSync() const noexcept override {return false;}
    };
}