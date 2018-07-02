#pragma once

//////////////////
//HEADERS
//////////////////
#include <Core/Export.hpp>
#include <Core/Input/KeyboardManager.hpp>
#include <Core/Input/MouseManager.hpp>
#include <Core/Input/JoystickManager.hpp>

namespace ax
{
    class AXION_CORE_API Input
    {
    public:
        friend class GameContext;
        friend class Game;

    protected:
        virtual void initialize() noexcept = 0;
        virtual void terminate() noexcept = 0;

    public:
        virtual KeyboardManager& keyboard() noexcept = 0;
        virtual MouseManager& mouse() noexcept = 0;
        virtual JoystickManager& joystick() noexcept = 0;
    };
}