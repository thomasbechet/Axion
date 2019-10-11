#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/NonCopyable.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Asset/Asset.hpp>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <atomic>
#include <sstream>

namespace ax
{
    class Asset;

    class AXION_CORE_API AssetLoader : public NonCopyable
    {
    public:
        struct Record
        {
            std::string str() const noexcept
            {
                std::stringstream ss;
                ss << std::left << ("[" + std::to_string(totalPending) + " " + std::to_string(totalLoaded) + " " 
                    + std::to_string(totalFailed) + "]");
                if(totalPending > 0)
                {
                    ss << " <" << currentAsset.type << "> '" << currentAsset.name << "'";
                }
                else
                {
                    ss << " Nothing to load";
                }
                
                return ss.str();
            }

            unsigned totalPending = 0;
            unsigned totalLoaded = 0;
            unsigned totalFailed = 0;
            Asset::Information currentAsset;
        };

    public:
        AssetLoader();
        ~AssetLoader();

        void restartRecord() noexcept;
        Record getRecord() noexcept;

    private:
        template<typename T>
        friend class AssetManager;

        void add(Asset& asset) noexcept;
        void wait(std::unique_lock<std::mutex>& lock) noexcept;
        void waitAll(std::unique_lock<std::mutex>& lock) noexcept;

    private:
        void routine() noexcept;

        std::thread m_thread;
        std::atomic<bool> m_running {true};
        std::mutex m_mutex;
        std::condition_variable m_loopCV;
        std::condition_variable m_loadedCV;

        std::vector<std::reference_wrapper<Asset>> m_assets;
        Record m_record;
    };
}