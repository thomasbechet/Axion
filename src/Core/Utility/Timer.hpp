#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/Time.hpp>

#include <chrono>

namespace ax
{
    class AXION_CORE_API Timer
    {
    public:
        void start() noexcept;
        void restart() noexcept;
        Time getElapsedTime() const noexcept;

    private:
        std::chrono::time_point<std::chrono::system_clock> m_start;
    };
}