#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>
#include <Core/Math/Vector.hpp>

namespace ax
{
    enum WindowMode
    {
        Fullscreen,
        Windowed,
        Borderless
    };

    class AXION_CORE_API Window
    {
    public:
        friend class GameContext;

    protected:
        virtual void initialize() noexcept = 0;
        virtual void terminate() noexcept = 0;
        virtual void update() noexcept = 0;

        virtual void swapBuffers() noexcept = 0;

    public:
        virtual ~Window(){}

        virtual bool requestGLContext() noexcept = 0;
        virtual bool requestDXContext() noexcept = 0;
        virtual bool requestVKContext() noexcept = 0;

        virtual bool shouldClose() noexcept = 0;

        virtual void setTitle(std::string title) noexcept = 0;
        virtual std::string getTitle() const noexcept = 0;
        virtual void setSize(Vector2u size) noexcept = 0;
        virtual Vector2u getSize() const noexcept = 0;
        virtual void setPosition(Vector2i position) noexcept = 0;
        virtual Vector2i getPosition() const noexcept = 0;
        virtual void setMode(WindowMode mode) noexcept = 0;
        virtual WindowMode getMode() noexcept = 0;
        virtual void setVerticalSync(bool toggle) noexcept = 0;
        virtual bool getVerticalSync() const noexcept = 0;
    };
}