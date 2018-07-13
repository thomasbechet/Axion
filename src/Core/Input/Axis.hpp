#pragma once

/////////////
//HEADERS
/////////////
#include <Core/Export.hpp>
#include <Core/Input/Mouse.hpp>
#include <Core/Input/Gamepad.hpp>
#include <Core/Input/InputType.hpp>

#include <string>

namespace ax
{
    class AXION_CORE_API Axis
    {
    public: 
        Axis(std::string name);

        float delta() noexcept;

        void bind(Mouse::Axis axis) noexcept;
        void bind(Gamepad::Axis axis) noexcept;

        void setSensibility(float s) noexcept;
        float getSensibility() const noexcept;

        std::string getName() const noexcept;
        InputType getType() const noexcept;

    private:
        InputType m_type = InputType::None;
        Mouse::Axis m_mouseInput;
        Gamepad::Axis m_gamepadInput;
        std::string m_name;
        float m_sensibility = 1.0f;
    };
}