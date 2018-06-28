#include <Core/Context/GameContext.hpp>

#include <Core/Context/Game.hpp>
#include <Core/System/SystemManager.hpp>
#include <Core/Logger/Logger.hpp>
#include <Core/Utility/ThreadPool.hpp>
#include <Core/World/World.hpp>

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
    if(isRunning()) return;

    m_running = true;

    //Configure Logger
    Game::logger().displayDate(Game::engine().config().getBoolean("Logger", "show_time", true));

    //Configure and start threadPool
    bool forceThread = Game::engine().config().getBoolean("Default", "force_thread_count", false);
    unsigned threadCount = (forceThread) ? Game::engine().config().getUnsigned("Default", "thread_count", 0) : 0;
    Game::threads().start(threadCount);

    //Starting clock
    m_timer.start();

    bool restart = true;
    while(restart)
    {
        restart = false;

        double lol = 3.434;

        if(Game::world().hasNextGameMode())
            Game::world().nextGameMode();

        //Game loop
        Game::world().getGameMode().onStart();
        Game::systems().start();

        const double dt = 1.0 / 60.0;
        double accumulator = 0.0;
        m_timer.restart();
        while(Game::engine().isRunning() && !Game::world().hasNextGameMode())
        {
            Time delta = m_timer.getElapsedTime();
            m_timer.restart();

            accumulator += delta.asSeconds();
            while(accumulator >= dt)
            {   
                accumulator -= dt;

                /*for(unsigned i = 0; i < 3135153; i++)
                {
                    lol = i / lol + i * lol;
                }*/

                m_deltaTime = Time((unsigned long long)(dt * 1000000000));

                Game::systems().update();
            }

            ax::Game::logger().log("rendering");
        }


        Game::systems().stop();
        Game::world().getGameMode().onStop();
    
        if(Game::world().hasNextGameMode()) restart = true;
    }

    //Removing all systems
    ax::Game::systems().removeAll();

    //Stopping threads
    Game::threads().stop();
}
void GameContext::stop() noexcept
{
    m_running = false;
}

Time GameContext::getDeltaTime() const noexcept
{
    return m_deltaTime;
}