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
        Time(unsigned long long time);

        Time operator+(const Time& time);
        Time operator-(const Time& time);

        unsigned long long asNanoseconds() const noexcept;
        float asMicroseconds() const noexcept;
        float asMilliseconds() const noexcept;
        double asSeconds() const noexcept;

        float asPercentage(unsigned frame = 60) const noexcept;
        
    private:
        unsigned long long m_time = 0;
    };
}