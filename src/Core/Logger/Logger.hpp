#pragma once

//////////////
//HEADERS
//////////////
#include <string>
#include <Core/Export.hpp>

#include <iostream>

namespace ax
{
    class AXION_CORE_API Logger
    {
    public:
        enum Severity
        {
            None,
            Info,
            Warning,
            Error,
            Fatal
        };

    public:
        virtual ~Logger(){}

        virtual void log(std::string message, Severity severity = Severity::None) noexcept = 0;
        virtual void displayDate(bool toggle) noexcept = 0;

        void log(unsigned value, Severity severity = Severity::None) noexcept;
        void log(int value, Severity severity = Severity::None) noexcept;
        void log(float value, Severity severity = Severity::None) noexcept;
        void log(double value, Severity severity = Severity::None) noexcept;
        void log(long value, Severity severity = Severity::None) noexcept;
        void log(unsigned long value, Severity severity = Severity::None) noexcept;
        void log(long long value, Severity severity = Severity::None) noexcept;
        void log(unsigned long long value, Severity severity = Severity::None) noexcept;
    };
}