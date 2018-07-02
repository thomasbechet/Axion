#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>
#include <Core/Math/Vector.hpp>

namespace ax
{
    class AXION_CORE_API Window
    {
    public:
        friend class GameContext;
        friend class Game;

    protected:
        virtual void initialize() noexcept = 0;
        virtual void terminate() noexcept = 0;

    public:
        virtual bool requestGLContext() noexcept = 0;
        virtual bool requestDXContext() noexcept = 0;
        virtual bool requestVKContext() noexcept = 0;

        virtual void setTitle(std::string title) noexcept = 0;
        virtual std::string getTitle() const noexcept = 0;
        virtual void setSize(Vector2u dimensions) noexcept = 0;
        virtual Vector2u getSize() const noexcept = 0;
    };
}