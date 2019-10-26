#pragma once

#include <Core/Export.hpp>
#include <Core/Asset/Asset.hpp>
#include <Core/Utility/NonCopyable.hpp>
#include <Core/Utility/Types.hpp>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <sstream>

namespace ax
{
    class Asset;

    class AXION_CORE_API AssetLoader : public NonCopyable
    {
    public:
        struct LoadState
        {
            std::string str() const noexcept
            {
                std::stringstream ss;
                ss << std::left << ("[P:" + std::to_string(totalPending) + " L:" + std::to_string(totalLoaded) + " F:" 
                    + std::to_string(totalFailed) + "]");
                if(isLoading)
                    ss << " <" << lastAsset.type << "> '" << lastAsset.name << "'";
                else
                    ss << " <NOT LOADING>";
                
                return ss.str();
            }

            bool isLoading = false;
            unsigned totalPending = 0;
            unsigned totalLoaded = 0;
            unsigned totalFailed = 0;
            Asset::Information lastAsset;
        };

    public:
        AssetLoader();
        ~AssetLoader();

        void resetLoadState() noexcept;
        LoadState getLoadState() noexcept;
        void waitAll() noexcept;

    private:
        template<typename T>
        friend class AssetManager;

        void add(Asset& asset) noexcept;
        void wait(std::unique_lock<std::mutex>& lock) noexcept;

    private:
        void routine() noexcept;

        std::thread m_thread;
        std::atomic<bool> m_running {true};
        std::mutex m_mutex;
        std::condition_variable m_loopCV;
        std::condition_variable m_loadedCV;

        std::vector<std::reference_wrapper<Asset>> m_assets;
        LoadState m_loadState;
    };
}