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
        struct State
        {
            std::string str() const noexcept
            {
                std::stringstream ss;
                ss << 
            }

            unsigned totalPending;
            unsigned totalLoaded;
            unsigned totalFailed;
            Asset::Information currentAsset;
        };

    public:
        AssetLoader();
        ~AssetLoader();

        void add(Asset& asset) noexcept;
        void wait(std::unique_lock<std::mutex>& lock) noexcept;
        State getState() noexcept;

    private:
        void routine() noexcept;

        std::thread m_thread;
        std::atomic<bool> m_running {true};

        std::mutex m_mutex;
        std::condition_variable m_loopCV;
        std::condition_variable m_loadedCV;

        std::vector<std::reference_wrapper<Asset>> m_assets;
        
        std::atomic<unsigned> m_totalPending {0};
        std::atomic<unsigned> m_totalLoaded {0};
        std::atomic<unsigned> m_totalFailed {0};
        Asset::Information m_currentAssetInformation;
    };
}