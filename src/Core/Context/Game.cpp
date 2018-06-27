#include <Core/Context/Game.hpp>

#include <Core/CoreSystems/NullRenderer.hpp>
#include <Core/System/SystemManager.hpp>
#include <Core/World/World.hpp>
#include <Core/Logger/NullLogger.hpp>
#include <Core/Logger/ConsoleLogger.hpp>
#include <Core/Utility/ThreadPool.hpp>
#include <Core/Context/GameContext.hpp>
#include <Core/Context/GameMode.hpp>

#include <Core/Utility/Timer.hpp>
#include <RuntimeTest/CustomSystem.hpp>

using namespace ax;

Renderer* Game::m_renderer = nullptr;
SystemManager* Game::m_systemManager = nullptr;
World* Game::m_world = nullptr;
Logger* Game::m_logger = nullptr;
ThreadPool* Game::m_threadPool = nullptr;
GameContext* Game::m_context = nullptr;

void Game::run() noexcept
{
    //Configure Logger
    logger().displayDate(Game::engine().config().getBoolean("Logger", "show_time", true));

    //Configure and start threadPool
    bool forceThread = Game::engine().config().getBoolean("Default", "force_thread_count", false);
    unsigned threadCount = (forceThread) ? Game::engine().config().getUnsigned("Default", "thread_count", 0) : 0;
    Game::threads().start(threadCount);

    bool restart = true;
    while(restart)
    {
        restart = false;

        if(Game::world().hasNextGameMode())
            Game::world().nextGameMode();

        //Game loop
        Game::world().getGameMode().onStart();
        Game::systems().start();
        while(Game::engine().isRunning() && !Game::world().hasNextGameMode())
        {
            Game::systems().update();
        }
        Game::systems().stop();
        Game::world().getGameMode().onStop();
    
        if(Game::world().hasNextGameMode()) restart = true;
    }

    //Stopping threads
    Game::threads().stop();
}

void Game::initialize() noexcept
{
    if(Game::engine().isRunning()) return;

    //Context
    m_context = new GameContext();
    m_context->config().parse("Engine.ini");

    //Systems control
    m_renderer = new NullRenderer();
    m_systemManager = new SystemManager();
    m_world = new World();

    //Logger
    std::string typeLogger = Game::engine().config().getString("Logger", "type", "none");
    if(typeLogger == "none") m_logger = new NullLogger();
    else if(typeLogger == "console") m_logger = new ConsoleLogger();

    //ThreadPool
    m_threadPool = new ThreadPool();
}
void Game::terminate() noexcept
{
    if(Game::engine().isRunning()) return;

    delete m_renderer;
    delete m_systemManager;
    delete m_world;

    delete m_threadPool; //ThreadPool depends on Logger

    delete m_logger;

    delete m_context;
}
void Game::interrupt(std::string message) noexcept
{
    Game::logger().log(message, Logger::Fatal);
    std::abort();
}

Renderer& Game::renderer() noexcept
{
    return *m_renderer;
}
SystemManager& Game::systems() noexcept
{
    return *m_systemManager;
}
World& Game::world() noexcept
{
    return *m_world;
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