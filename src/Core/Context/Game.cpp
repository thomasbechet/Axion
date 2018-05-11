#include <Core/Context/Game.hpp>

#include <cstdlib>
#include <Core/CoreSystems/NullRenderer.hpp>
#include <Core/Entity/EntityManager.hpp>
#include <Core/Logger/NullLogger.hpp>
#include <Core/Logger/ConsoleLogger.hpp>
#include <Core/Entity/ComponentManager.hpp>
#include <Core/Utility/ThreadPool.hpp>

using namespace ax;

Renderer* Game::m_renderer = nullptr;
EntityManager* Game::m_entityManager = nullptr;
ComponentManager* Game::m_componentManager = nullptr;
Logger* Game::m_logger = nullptr;
ThreadPool* Game::m_threadPool = nullptr;

void Game::initialize() noexcept
{
    //Systems control
    m_renderer = new NullRenderer();
    m_componentManager = new ComponentManager();
    m_entityManager = new EntityManager(*m_componentManager);

    //Logger
    m_logger = new ConsoleLogger();

    //ThreadPool
    m_threadPool = new ThreadPool();
}
void Game::terminate() noexcept
{
    delete m_renderer;
    delete m_entityManager;
    delete m_componentManager;
    delete m_logger;

    delete m_threadPool;
}
void Game::interrupt(std::string message) noexcept
{
    Game::logger().log(message, Logger::FATAL);
    std::abort();
}

void Game::start() noexcept
{
    
}
void Game::stop() noexcept
{
    
}

Renderer& Game::renderer() noexcept
{
    return *m_renderer;
}
EntityManager& Game::entities() noexcept
{
    return *m_entityManager;
}
ComponentManager& Game::components() noexcept
{
    return *m_componentManager;
}
Logger& Game::logger() noexcept
{
    return *m_logger;
}
ThreadPool& Game::threads() noexcept
{
    return *m_threadPool;
}