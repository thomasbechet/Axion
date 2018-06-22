#pragma once

///////////////////
//HEADERS
///////////////////
#include <Core/Export.hpp>
#include <Core/Utility/ConfigParser.hpp>

namespace ax
{
    class AXION_CORE_API GameContext
    {
    public:
        ConfigParser& config() noexcept;

        bool isRunning() const noexcept;
        void start() noexcept;
        void stop() noexcept;

    private:
        ConfigParser m_configParser;
        bool m_running = false;
    };
}