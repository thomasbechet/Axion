#include <Core/Utility/Time.hpp>

using namespace ax;

Time::Time(){}
Time::Time(unsigned long long time)
{
    m_time = time;
}

Time Time::operator+(const Time& time)
{
    return Time(m_time + time.m_time);
}
Time Time::operator-(const Time& time)
{
    return Time(m_time - time.m_time);
}

unsigned long long Time::asNanoseconds() const noexcept
{
    return m_time;
}
float Time::asMicroseconds() const noexcept
{
    return (float)m_time / 1000.0f;
}
float Time::asMilliseconds() const noexcept
{
    return (float)m_time / 1000000.0f;
}
double Time::asSeconds() const noexcept
{
    return (double)m_time / 1000000000.0;
}

float Time::asPercentage(unsigned frame) const noexcept
{
    return (float)((asSeconds() * (double)frame) * 100.0); //=(seconds / (1/frame)) * 100
}