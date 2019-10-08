#include <Core/Asset/AssetLoader.hpp>

#include <Core/Asset/Asset.hpp>

using namespace ax;

AssetLoader::AssetLoader()
{
    m_thread = std::thread(&AssetLoader::routine, this);
}
AssetLoader::~AssetLoader()
{
    m_running = false;
    m_loopCV.notify_one();

    if(m_thread.joinable())
        m_thread.join();
}

void AssetLoader::add(Asset& asset) noexcept
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_assets.emplace_back(asset);
    m_totalPending++;
    m_loopCV.notify_one();
}
void AssetLoader::wait(std::unique_lock<std::mutex>& lock) noexcept
{
    m_loadedCV.wait(lock);
}
AssetLoader::State AssetLoader::getState() noexcept
{
    std::lock_guard<std::mutex> lock(m_mutex);
    
    State state;
    state.totalPending = m_totalPending;
    state.totalLoaded = m_totalLoaded;
    state.totalFailed = m_totalFailed;
    state.currentAsset = m_currentAssetInformation;

    return state;
}

void AssetLoader::routine() noexcept
{
    while(true)
    {
        std::unique_lock<std::mutex> lock(m_mutex);

        m_loopCV.wait(lock, [&](){return !m_assets.empty() || !m_running;});
        if(!m_running) break;

        Asset& asset = m_assets.back();
        m_assets.pop_back();
        m_currentAssetInformation = asset.getInformation();
        lock.unlock();

        if(asset.load()) 
            m_totalLoaded++;
        else 
            m_totalFailed++;
        m_totalPending--;

        if(m_totalPending == 0)
        {
            lock.lock();
            m_currentAssetInformation = Asset::Information();
            lock.unlock();
        }
        m_loadedCV.notify_all();
    }
}