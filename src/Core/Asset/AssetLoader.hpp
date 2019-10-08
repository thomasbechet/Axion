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

namespace ax
{
    class Asset;

    class AXION_CORE_API AssetLoader : public NonCopyable
    {
    public:
        AssetLoader();
        ~AssetLoader();

        void add(Asset& asset) noexcept;
        void wait(std::unique_lock<std::mutex>& lock) noexcept;
        unsigned getTotalPending() noexcept;
        Asset::Information getCurrentAssetInformation() noexcept;

    private:
        void routine() noexcept;

        std::thread m_thread;

        std::mutex m_mutex;
        std::condition_variable m_loopCV;
        std::condition_variable m_loadedCV;

        std::vector<std::reference_wrapper<Asset>> m_assets;

        std::atomic<bool> m_running {true};
        std::atomic<unsigned> m_totalPending {0};
        Asset::Information m_currentAssetInformation;
    };
}