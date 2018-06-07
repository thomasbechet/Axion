#include <Core/Logger/Logger.hpp>

using namespace ax;

void Logger::log(unsigned value, Severity severity) noexcept
{
    log(std::to_string(value), severity);
}
void Logger::log(int value, Severity severity) noexcept
{
    log(std::to_string(value), severity);
}
void Logger::log(float value, Severity severity) noexcept
{
    log(std::to_string(value), severity);
}
void Logger::log(double value, Severity severity) noexcept
{
    log(std::to_string(value), severity);
}