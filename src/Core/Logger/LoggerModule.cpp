#include <Core/Logger/LoggerModule.hpp>

using namespace ax;

void LoggerModule::log(unsigned value, Severity severity) noexcept
{
    log(std::to_string(value), severity);
}
void LoggerModule::log(int value, Severity severity) noexcept
{
    log(std::to_string(value), severity);
}
void LoggerModule::log(float value, Severity severity) noexcept
{
    log(std::to_string(value), severity);
}
void LoggerModule::log(double value, Severity severity) noexcept
{
    log(std::to_string(value), severity);
}
void LoggerModule::log(long value, Severity severity) noexcept
{
    log(std::to_string(value), severity);
}
void LoggerModule::log(unsigned long value, Severity severity) noexcept
{
    log(std::to_string(value), severity);
}
void LoggerModule::log(long long value, Severity severity) noexcept
{
    log(std::to_string(value), severity);
}
void LoggerModule::log(unsigned long long value, Severity severity) noexcept
{
    log(std::to_string(value), severity);
}