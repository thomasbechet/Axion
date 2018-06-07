#include <Core/Context/Game.hpp>

#include <Core/CoreSystems/NullRenderer.hpp>
#include <Core/System/SystemManager.hpp>
#include <Core/Entity/EntityManager.hpp>
#include <Core/Logger/NullLogger.hpp>
#include <Core/Logger/ConsoleLogger.hpp>
#include <Core/Entity/ComponentManager.hpp>
#include <Core/Utility/ThreadPool.hpp>
#include <Core/Context/GameContext.hpp>

using namespace ax;

Renderer* Game::m_renderer = nullptr;
SystemManager* Game::m_systemManager = nullptr;
EntityManager* Game::m_entityManager = nullptr;
ComponentManager* Game::m_componentManager = nullptr;
Logger* Game::m_logger = nullptr;
ThreadPool* Game::m_threadPool = nullptr;
GameContext* Game::m_context = nullptr;

void Game::initialize() noexcept
{
    //Context
    m_context = new GameContext();
    m_context->config().parse("Engine.ini");

    //Systems control
    m_renderer = new NullRenderer();
    m_systemManager = new SystemManager();
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
    delete m_systemManager;
    delete m_entityManager;
    delete m_componentManager;

    delete m_threadPool; //ThreadPool depends on Logger

    delete m_logger;

    delete m_context;
}
void Game::interrupt(std::string message) noexcept
{
    Game::logger().log(message, Logger::FATAL);
    std::abort();
}

void Game::start() noexcept
{
    //Configure Logger
    logger().displayDate(Game::engine().config().getBoolean("Logger", "show_time", true));

    //Configure and start threadPool
    bool forceThread = Game::engine().config().getBoolean("Default", "force_thread_count", false);
    unsigned threadCount = (forceThread) ? Game::engine().config().getUnsigned("Default", "thread_count", 0) : 0;
    Game::threads().start(threadCount);
}
void Game::stop() noexcept
{
    Game::threads().stop();
}

Renderer& Game::renderer() noexcept
{
    return *m_renderer;
}
SystemManager& Game::systems() noexcept
{
    return *m_systemManager;
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
GameContext& Game::engine() noexcept
{
    return *m_context;
}