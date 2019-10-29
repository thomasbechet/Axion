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

void AssetLoader::resetLoadState() noexcept
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_loadState.totalPending = m_assets.size();
    m_loadState.totalLoaded = 0;
    m_loadState.totalFailed = 0;
}
AssetLoader::LoadState AssetLoader::getLoadState() noexcept
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_loadState;
}
void AssetLoader::waitAll() noexcept
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_loadedCV.wait(lock, [&]() -> bool {
        return !m_loadState.isLoading;});
}

void AssetLoader::add(Asset& asset) noexcept
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_assets.emplace_back(asset);
    m_loadState.totalPending = m_assets.size();
    m_loadState.isLoading = true;
    lock.unlock();
    m_loopCV.notify_one();
}
void AssetLoader::wait(std::unique_lock<std::mutex>& lock) noexcept
{
    m_loadedCV.wait(lock);
}

void AssetLoader::routine() noexcept
{
    while(true)
    {
        std::unique_lock<std::mutex> lock(m_mutex);

        while(m_assets.empty() && m_running) 
        {
            m_loadState.isLoading = false;
            m_loadState.lastAsset = Asset::Information();
            m_loopCV.wait(lock);
        }

        if(!m_running) break;

        m_loadState.isLoading = true;

        Asset& asset = m_assets.back();
        m_assets.pop_back();
        m_loadState.lastAsset = asset.getInformation();
        m_loadState.totalPending = m_assets.size();
        lock.unlock();

        bool success = asset.load();

        lock.lock();
        if(success) 
            m_loadState.totalLoaded++;
        else 
            m_loadState.totalFailed++;

        lock.unlock();

        m_loadedCV.notify_all();
    }
}