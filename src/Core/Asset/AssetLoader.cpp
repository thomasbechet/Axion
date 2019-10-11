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

void AssetLoader::restartRecord() noexcept
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_record = Record();
    m_record.totalPending = m_assets.size();
}
AssetLoader::Record AssetLoader::getRecord() noexcept
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_record;
}

void AssetLoader::add(Asset& asset) noexcept
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_assets.emplace_back(asset);
    m_record.totalPending++;
    m_loopCV.notify_one();
}
void AssetLoader::wait(std::unique_lock<std::mutex>& lock) noexcept
{
    m_loadedCV.wait(lock);
}
void AssetLoader::waitAll(std::unique_lock<std::mutex>& lock) noexcept
{
    m_loadedCV.wait(lock, [&]() -> bool {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_record.totalPending == 0;});
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
        m_record.currentAsset = asset.getInformation();
        lock.unlock();

        if(asset.load()) 
            m_record.totalLoaded++;
        else 
            m_record.totalFailed++;
        m_record.totalLoaded--;

        if(m_record.totalPending == 0)
        {
            lock.lock();
            m_record.currentAsset = Asset::Information();
            lock.unlock();
        }
        m_loadedCV.notify_all();
    }
}