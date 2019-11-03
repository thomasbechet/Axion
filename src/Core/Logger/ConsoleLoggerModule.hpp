#pragma once

#include <Core/Export.hpp>
#include <Core/Logger/ThreadSafeLoggerModule.hpp>

namespace ax
{
    class AXION_CORE_API ConsoleLoggerModule : public ThreadSafeLoggerModule
    {
    protected:
        void onLog(const std::string& message, Severity severity) noexcept override;
        void displayDate(bool toggle) noexcept override;

    private:
        bool m_date = true;
    };
}