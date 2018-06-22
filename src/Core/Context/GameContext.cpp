#include <Core/Context/GameContext.hpp>

#include <Core/Context/Game.hpp>

using namespace ax;

ConfigParser& GameContext::config() noexcept
{
    return m_configParser;
}

bool GameContext::isRunning() const noexcept
{
    return m_running;
}

void GameContext::start() noexcept
{
    m_running = true;
    Game::run();
}
void GameContext::stop() noexcept
{
    m_running = false;
}