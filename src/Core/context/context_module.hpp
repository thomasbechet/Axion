#pragma once

#include <core/export.hpp>
#include <core/engine/module.hpp>
#include <core/utility/config_parser.hpp>
#include <core/utility/thread_pool.hpp>
#include <core/utility/time.hpp>
#include <core/utility/timer.hpp>

namespace ax::detail
{
    class AXION_CORE_API context_module : public module
    {
    public:
        context_module(path configuration_file);

        void initialize() noexcept override;
        void terminate() noexcept override;

        bool is_running() const noexcept;
        void run() noexcept;
        void request_stop() noexcept;

        time get_delta_time() const noexcept;

    public:
        detail::config_parser config;
        detail::thread_pool thread;

    private:
        bool m_running = false;
        timer m_timer;
        time m_delta_time;

    private:
        void pre_run() noexcept;
    };
}