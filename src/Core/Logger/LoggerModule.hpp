#pragma once

#include <Core/Export.hpp>

#include <string>

namespace ax
{
    enum Severity
    {
        None,
        Info,
        Warning,
        Error,
        Fatal
    };

    namespace detail
    {
        class AXION_CORE_API LoggerModule
        {
        public:
            virtual ~LoggerModule() = default;

            virtual void initialize() noexcept = 0;
            virtual void terminate() noexcept = 0;

            virtual void log(const std::string& message, Severity severity = Severity::None) noexcept = 0;
            virtual void displayDate(bool toggle) noexcept = 0;
            virtual void flush() noexcept = 0;
        };
    }
}