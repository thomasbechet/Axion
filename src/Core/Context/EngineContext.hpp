#pragma once

///////////////////
//HEADERS
///////////////////
#include <Core/Export.hpp>
#include <Core/Utility/NonCopyable.hpp>
#include <Core/Utility/ConfigParser.hpp>
#include <Core/Utility/Time.hpp>
#include <Core/Utility/Timer.hpp>

namespace ax
{
    class AXION_CORE_API EngineContext : public NonCopyable
    {
    public:
        ConfigParser& config() noexcept;

        bool isRunning() const noexcept;
        void run() noexcept;
        void requestStop() noexcept;

        Time getDeltaTime() const noexcept;

    private:
        ConfigParser m_configParser;
        bool m_running = false;
        Timer m_timer;
        Time m_deltaTime;
    };
}