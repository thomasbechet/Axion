#pragma once

#include <Core/Export.hpp>

namespace ax
{
    class AXION_CORE_API Time
    {
    public:
        static Time make_seconds(double seconds) noexcept;
        static Time make_milliseconds(float milliseconds) noexcept;
        static Time make_microseconds(float microseconds) noexcept;
        static Time make_nanoseconds(unsigned long long nanoseconds) noexcept;

        Time();
        Time(unsigned long long nanoseconds);
        Time(double seconds);

        Time operator+(const Time& time);
        Time operator-(const Time& time);
        Time operator*(const Time& time);
        Time operator/(const Time& time);
        Time operator/(unsigned k);
        Time& operator+=(const Time& time);
        Time& operator-=(const Time& time);
        bool operator>(const Time& t) const;
        bool operator>=(const Time& t) const;
        bool operator<(const Time& t) const;
        bool operator<=(const Time& t) const;
        bool operator==(const Time& t) const;
        bool operator!=(const Time& t) const;

        unsigned long long asNanoseconds() const noexcept;
        float asMicroseconds() const noexcept;
        float asMilliseconds() const noexcept;
        double asSeconds() const noexcept;

        float asPercentage(unsigned frame = 60) const noexcept;
        
    private:
        unsigned long long m_time = 0;
    };
}