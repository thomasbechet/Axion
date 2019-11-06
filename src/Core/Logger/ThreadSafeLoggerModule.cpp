#include <Core/Logger/ThreadSafeLoggerModule.hpp>

using namespace ax;

void ThreadSafeLoggerModule::initialize() noexcept
{
    m_thread = std::thread(&ThreadSafeLoggerModule::routine, this);
}
void ThreadSafeLoggerModule::terminate() noexcept
{
    m_running = false;
    m_newMessageCD.notify_one();
    m_thread.join();
}

void ThreadSafeLoggerModule::log(const std::string& message, Severity severity) noexcept
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_queue.push(std::make_pair(message, severity));
    m_newMessageCD.notify_one();
}
void ThreadSafeLoggerModule::flush() noexcept
{
    std::unique_lock<std::mutex> lock(m_mutex);
    while(!m_queue.empty()) m_flushCD.wait(lock);
}

void ThreadSafeLoggerModule::routine() noexcept
{
    bool empty = false;
    while(true)
    {
        std::unique_lock<std::mutex> lock(m_mutex);

        if(empty) m_flushCD.notify_one();

        while(m_queue.empty() && m_running) m_newMessageCD.wait(lock);
        if(!m_running) break;

        auto pair = m_queue.front();
        m_queue.pop();

        empty = m_queue.empty();

        lock.unlock();

        onLog(pair.first, pair.second);
    }
}