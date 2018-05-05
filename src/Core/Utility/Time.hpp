#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>

namespace ax
{
    class AXION_CORE_API Time
    {
    public:
        Time();
        Time(long time);

        Time operator+(const Time& time);
        Time operator-(const Time& time);

        long asNanoseconds() const noexcept;
        float asMicroseconds() const noexcept;
        float asMilliseconds() const noexcept;
        double asSeconds() const noexcept;
        
    private:
        long m_time = 0;
    };
}