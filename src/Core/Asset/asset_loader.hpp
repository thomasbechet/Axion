#pragma once

#include <core/export.hpp>
#include <core/asset/asset.hpp>
#include <core/utility/non_copyable.hpp>
#include <core/utility/types.hpp>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <sstream>

namespace ax
{
    class asset;

    class AXION_CORE_API asset_loader : public non_copyable
    {
    public:
        struct load_state
        {
            std::string str() const noexcept
            {
                std::stringstream ss;
                ss << std::left << ("[P:" + std::to_string(total_pending) + " L:" + std::to_string(total_loaded) + " F:" 
                    + std::to_string(total_failed) + "]");
                if(is_loading)
                    ss << " <" << last_asset.identifier << "> '" << last_asset.name << "'";
                else
                    ss << " <NOT LOADING>";
                
                return ss.str();
            }

            bool is_loading = false;
            unsigned total_pending = 0;
            unsigned total_loaded = 0;
            unsigned total_failed = 0;
            asset::information last_asset;
        };

    public:
        asset_loader();
        ~asset_loader();

        void resetload_state() noexcept;
        load_state getload_state() noexcept;
        void wait_all() noexcept;

    private:
        template<typename type>
        friend class asset_manager;

        void add(asset& asset) noexcept;
        void wait(std::unique_lock<std::mutex>& lock) noexcept;

    private:
        void routine() noexcept;

        std::thread m_thread;
        std::atomic<bool> m_running {true};
        std::mutex m_mutex;
        std::condition_variable m_loop_cv;
        std::condition_variable m_loaded_cv;

        std::vector<std::reference_wrapper<asset>> m_assets;
        load_state m_load_state;
    };
}