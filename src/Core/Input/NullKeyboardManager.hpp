#pragma once

///////////////////
//HEADERS
///////////////////
#include <Core/Export.hpp>
#include <Core/Input/KeyboardManager.hpp>

namespace ax
{
    class AXION_CORE_API NullKeyboardManager : public KeyboardManager
    {
    public:
        bool isKeyPressed(Keyboard key) const noexcept override {return false;}
        bool isKeyReleased(Keyboard key) const noexcept override {return false;}
    };
}