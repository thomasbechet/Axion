#include <Core/Utility/ThreadPool.hpp>
#include <iostream>

using namespace ax;

ThreadPool::ThreadPool() : m_running(true), m_task_size(0), m_job_size(0)
{
    int proc_count = std::thread::hardware_concurrency();
    m_thread_count = (proc_count > 0) ? proc_count : 1;

    for(size_t i = 0; i < m_thread_count; i++)
    {
        m_threads.push_back(std::thread(&ThreadPool::worker_main, this));
    }

    std::cout << "[" << m_thread_count << " threads created]" << std::endl;
}
ThreadPool::~ThreadPool()
{
    std::unique_lock<std::mutex> lock(m_mutex);

    m_running = false;

    m_cv_worker.notify_all();
    lock.unlock();

    for(std::vector<std::thread>::iterator it = m_threads.begin(); it != m_threads.end(); it++)
    {
        it->join();
    }

    std::cout << "[" << m_thread_count << " threads destroyed]" << std::endl;
}

ThreadPool::Task ThreadPool::createTask() noexcept
{
    std::lock_guard<std::mutex> lock(m_mutex);
    Task task;

    if(m_free_tasks.empty())
    {
        task = (Task)m_task_size;
        m_task_size++;
        m_task_pending_count.resize(m_task_size);
    }
    else
    {
        task = m_free_tasks.back();
        m_free_tasks.pop_back();
    }
    m_task_pending_count[task] = 0;

    return task;
}
bool ThreadPool::isTaskFinished(Task task) const noexcept
{
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_task_pending_count[task] == 0;
}
void ThreadPool::performTask(Task task, const Job& job) noexcept
{
    std::lock_guard<std::mutex> lock(m_mutex);

    m_job_task.push_back(task);
    m_job_function.push_back(job);
    m_task_pending_count[task]++;
    m_job_size++;
    m_cv_worker.notify_one();
}
void ThreadPool::waitTask(Task task) noexcept
{
    std::unique_lock<std::mutex> lock(m_mutex);

    while(m_task_pending_count[task] > 0)
        m_cv_master.wait(lock);

    m_free_tasks.push_back(task);
}

void ThreadPool::worker_main()
{
    std::unique_lock<std::mutex> lock(m_mutex);

    while(m_running)
    {
        m_cv_worker.wait(lock);

        while(true)
        {
            if(m_job_size == 0) break;

            Task task = m_job_task.back();
            Job job = m_job_function.back();
            m_job_task.pop_back();
            m_job_function.pop_back();
            m_job_size--;

            lock.unlock(); //Unlock during job execution

            job();

            lock.lock();
            m_task_pending_count[task]--;
            if(m_task_pending_count[task] == 0)
                m_cv_master.notify_all();
        }
    }
}