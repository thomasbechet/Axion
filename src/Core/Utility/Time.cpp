#include <Core/Utility/Time.hpp>

using namespace ax;

Time Time::make_seconds(double seconds) noexcept
{
    return Time((unsigned long long)(seconds * 1000000000.0));
}
Time Time::make_milliseconds(float milliseconds) noexcept
{
    return Time((unsigned long long)(milliseconds * 1000000.0f));
}
Time Time::make_microseconds(float microseconds) noexcept
{
    return Time((unsigned long long)(microseconds * 1000.0f));
}
Time Time::make_nanoseconds(unsigned long long nanoseconds) noexcept
{
    return Time(nanoseconds);
}

Time::Time(){}
Time::Time(unsigned long long nanoseconds)
{
    m_time = nanoseconds;
}

Time Time::operator+(const Time& time)
{
    return Time(m_time + time.m_time);
}
Time Time::operator-(const Time& time)
{
    return Time(m_time - time.m_time);
}
Time Time::operator*(const Time& time)
{
    return Time(m_time * time.m_time);
}
Time Time::operator/(const Time& time)
{
    return Time(m_time / time.m_time);
}
Time Time::operator/(unsigned k)
{
    return Time(m_time / k);
}
Time& Time::operator+=(const Time& time)
{
    this->m_time += time.m_time;
    return *this;
}
Time& Time::operator-=(const Time& time)
{
    this->m_time -= time.m_time;
    return *this;
}
bool Time::operator>(const Time& t) const
{
    return this->m_time > t.m_time;
}
bool Time::operator>=(const Time& t) const
{
    return this->m_time >= t.m_time;
}
bool Time::operator<(const Time& t) const
{
    return this->m_time < t.m_time;
}
bool Time::operator<=(const Time& t) const
{
    return this->m_time <= t.m_time;
}
bool Time::operator==(const Time& t) const
{
    return this->m_time == t.m_time;
}
bool Time::operator!=(const Time& t) const
{
    return this->m_time != t.m_time;
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