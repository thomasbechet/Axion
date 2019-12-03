#include <core/asset/asset_loader.hpp>

#include <core/asset/asset.hpp>

using namespace ax;

asset_loader::asset_loader()
{
    m_thread = std::thread(&_asset_loader::routine, this);
}
asset_loader::~asset_loader()
{
    m_running = false;
    m_loop_cv.notify_one();

    if(m_thread.joinable())
        m_thread.join();
}

void asset_loader::reset_load_state() noexcept
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_load_state.total_pending = m_assets.size();
    m_load_state.total_loaded = 0;
    m_load_state.total_failed = 0;
}
asset_loader::load_state asset_loader::get_load_state() noexcept
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_load_state;
}
void asset_loader::wait_all() noexcept
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_loaded_cv.wait(lock, [&]() -> bool {
        return !m_load_state.is_loading;});
}

void asset_loader::add(asset& asset) noexcept
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_assets.emplace_back(asset);
    m_load_state.total_pending = m_assets.size();
    m_load_state.is_loading = true;
    lock.unlock();
    m_loop_cv.notify_one();
}
void asset_loader::wait(std::unique_lock<std::mutex>& lock) noexcept
{
    m_loaded_cv.wait(lock);
}

void asset_loader::routine() noexcept
{
    while(true)
    {
        std::unique_lock<std::mutex> lock(m_mutex);

        while(m_assets.empty() && m_running) 
        {
            m_load_state.is_loading = false;
            m_load_state.last_asset = asset::information();
            m_loop_cv.wait(lock);
        }

        if(!m_running) break;

        m_load_state.is_loading = true;

        asset& asset = m_assets.back();
        m_assets.pop_back();
        m_load_state.last_asset = asset.get_information();
        m_load_state.total_pending = m_assets.size();
        lock.unlock();

        bool success = asset.load();

        lock.lock();
        if(success) 
            m_load_state.total_loaded++;
        else 
            m_load_state.total_failed++;

        lock.unlock();

        m_loaded_cv.notify_all();
    }
}