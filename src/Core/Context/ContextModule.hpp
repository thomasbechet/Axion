#pragma once

#include <Core/Export.hpp>
#include <Core/Context/Module.hpp>
#include <Core/Utility/ConfigParser.hpp>
#include <Core/Utility/ThreadPool.hpp>
#include <Core/Utility/Time.hpp>
#include <Core/Utility/Timer.hpp>

namespace ax
{
    class AXION_CORE_API ContextModule : public Module
    {
    public:
        bool isRunning() const noexcept;
        void run() noexcept;
        void requestStop() noexcept;

        Time getDeltaTime() const noexcept;

    public:
        ConfigParser config;
        ThreadPool thread;

    private:
        ConfigParser m_configParser;
        bool m_running = false;
        Timer m_timer;
        Time m_deltaTime;

    private:
        void preRun() noexcept;
    };
}