#include <Core/Utility/Timer.hpp>

#include <chrono>

using namespace ax;

using systemClock = std::chrono::high_resolution_clock;

void Timer::start() noexcept
{
    m_start = systemClock::now();
}
void Timer::restart() noexcept
{
    start();
}
Time Timer::getElapsedTime() const noexcept
{
    std::chrono::time_point<std::chrono::system_clock> stop = systemClock::now();
    return Time(std::chrono::duration_cast<std::chrono::nanoseconds>(stop - m_start).count());
}