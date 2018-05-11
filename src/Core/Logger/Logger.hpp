#pragma once

//////////////
//HEADERS
//////////////
#include <string>
#include <Core/Export.hpp>

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
        virtual void log(std::string message, Severity severity = Severity::NONE) noexcept = 0;
        virtual void displayDate(bool toggle) noexcept = 0;
    };
}