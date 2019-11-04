#include <Core/Logger/ThreadSafeLoggerModule.hpp>

using namespace ax;

void ThreadSafeLoggerModule::initialize() noexcept
{
    m_thread = std::thread(&ThreadSafeLoggerModule::routine, this);
}
void ThreadSafeLoggerModule::terminate() noexcept
{
    m_running = false;
    m_conditionVariable.notify_one();
    m_thread.join();
}

void ThreadSafeLoggerModule::log(const std::string& message, Severity severity) noexcept
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_queue.push(std::make_pair(message, severity));
    m_conditionVariable.notify_one();
}
void ThreadSafeLoggerModule::flush() noexcept
{
    std::lock_guard<std::mutex> lock(m_mutex);
    while(!m_queue.empty())
    {
        auto pair = m_queue.front();
        m_queue.pop();
        onLog(pair.first, pair.second);
    }
}

void ThreadSafeLoggerModule::routine() noexcept
{
    while(true)
    {
        std::unique_lock<std::mutex> lock(m_mutex);

        while(m_queue.empty() && m_running) m_conditionVariable.wait(lock);
        if(!m_running) break;

        auto pair = m_queue.front();
        m_queue.pop();

        lock.unlock();

        onLog(pair.first, pair.second);
    }
}