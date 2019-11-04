#pragma once

#include <Core/Export.hpp>
#include <Core/Logger/LoggerModule.hpp>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <queue>

namespace ax
{
    class AXION_CORE_API ThreadSafeLoggerModule : public LoggerModule
    {
    public:
        void initialize() noexcept override;
        void terminate() noexcept override;

        void log(const std::string& message, Severity severity = Severity::None) noexcept override;
        void flush() noexcept override;

    protected:
        virtual void onLog(const std::string& message, Severity severity) noexcept = 0;

    private:
        void routine() noexcept;

        std::thread m_thread;
        std::mutex m_mutex;
        std::condition_variable m_conditionVariable;
        std::atomic<bool> m_running {true};
        std::queue<std::pair<std::string, Severity>> m_queue;
    };
}