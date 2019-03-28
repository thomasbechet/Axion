#pragma once

#include <Core/Export.hpp>
#include <Core/Logger/Logger.hpp>

namespace ax
{
    class AXION_CORE_API ConsoleLogger : public Logger
    {
    public:
        void log(std::string message, Severity severity) noexcept override;
        void displayDate(bool toggle) noexcept override;

    private:
        bool m_date = true;
    };
}