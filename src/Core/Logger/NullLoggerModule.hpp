#pragma once

#include <Core/Export.hpp>
#include <Core/Logger/LoggerModule.hpp>

namespace ax::detail
{
    class AXION_CORE_API NullLoggerModule : public LoggerModule
    {
    public:
        void initialize() noexcept override {}
        void terminate() noexcept override {}

        void log(const std::string& message, Severity severity) noexcept override {}
        void displayDate(bool toggle) noexcept override {}
        void flush() noexcept override {}
    };
}