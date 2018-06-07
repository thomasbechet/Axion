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
            NONE,
            INFO,
            WARNING,
            ERROR,
            FATAL
        };

    public:
        virtual ~Logger(){}

        virtual void log(std::string message, Severity severity = Severity::NONE) noexcept = 0;
        virtual void displayDate(bool toggle) noexcept = 0;

        void log(unsigned value, Severity severity = Severity::NONE) noexcept;
        void log(int value, Severity severity = Severity::NONE) noexcept;
        void log(float value, Severity severity = Severity::NONE) noexcept;
        void log(double value, Severity severity = Severity::NONE) noexcept;
    };
}