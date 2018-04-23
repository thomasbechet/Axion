#pragma once

//////////////////
//HEADERS
//////////////////
#include <Core/Export.hpp>
#include <Core/Utility/NonCopyable.hpp>

#include <functional>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <algorithm>

namespace ax
{
    using Task = int;

    class AXION_CORE_API ThreadPool : public NonCopyable
    {
    public:
        using Job = std::function<void(void)>;

    public:
        inline ThreadPool();
        inline ~ThreadPool();

        Task createTask();
        bool isTaskFinished(Task task) const
        void performTask(Task task, const Job& job);
        void waitTask(Task task);

    private:
        void worker_main();

        bool m_running;
        mutable std::mutex m_mutex;
        std::vector<std::thread> m_threads;
        size_t m_thread_count;

        size_t m_task_size;
        std::vector<Task> m_free_tasks;
        std::vector<size_t> m_task_pending_count;

        size_t m_job_size;
        std::vector<Task> m_job_task;
        std::vector<Job> m_job_function;

        std::condition_variable m_cv_worker;
        std::condition_variable m_cv_master;
    };
}

