#include <Core/Scene/GameMode/GameModeManager.hpp>

using namespace ax;

GameModeManager::GameModeManager()
{
    m_gameMode = std::make_unique<GameMode>();
}

GameMode& GameModeManager::get() const noexcept
{
    return *m_gameMode.get();
}

bool GameModeManager::hasNext() const noexcept
{
    return (m_nextGameMode != nullptr);
}
void GameModeManager::next() noexcept
{
    if(!hasNext()) return;

    m_gameMode.swap(m_nextGameMode);
    m_nextGameMode.reset();
}