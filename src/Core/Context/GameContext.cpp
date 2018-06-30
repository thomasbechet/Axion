#include <Core/Context/GameContext.hpp>

#include <Core/Context/Game.hpp>
#include <Core/System/SystemManager.hpp>
#include <Core/Logger/Logger.hpp>
#include <Core/Utility/ThreadPool.hpp>
#include <Core/Utility/TimeRecorder.hpp>
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

    //Frame recorder
    TimeRecorder frameRecorder = TimeRecorder(10);
    Timer frameRecorderTimer;
    frameRecorderTimer.start();

    //Starting clock
    m_timer.start();

    bool restart = true;
    while(restart)
    {
        restart = false;

        if(Game::world().hasNextGameMode())
            Game::world().nextGameMode();

        //Game loop
        Game::world().getGameMode().onStart();
        Game::systems().start();

        double fixed_timestep = Game::engine().config().getDouble("Time", "fixed_timestep", 1.0 / 50.0);
        double maximum_timestep = Game::engine().config().getDouble("Time", "maximum_timestep", 1.0 / 10.0);
        const Time FIXED_TIMESTEP = Time::make_seconds(fixed_timestep);
        const Time MAXIMUM_TIMESTEP = Time::make_seconds(maximum_timestep);

        if(FIXED_TIMESTEP > MAXIMUM_TIMESTEP)
            Game::interrupt("Fixed-Timestep (" + std::to_string(FIXED_TIMESTEP.asSeconds()) + ") higher than Maximum-Timestep (" + std::to_string(MAXIMUM_TIMESTEP.asSeconds()) + ")");


        Time accumulator = Time::make_seconds(0.0);
        m_timer.restart();
        while(Game::engine().isRunning() && !Game::world().hasNextGameMode())
        {
            Time delta = m_timer.getElapsedTime();
            
            m_timer.restart();

            if(delta > MAXIMUM_TIMESTEP)
            {
                delta = MAXIMUM_TIMESTEP;
                std::cout << "maximum reached" << std::endl;
            }

            accumulator += delta;

            while(accumulator >= FIXED_TIMESTEP)
            {   
                Timer test_logic_timer;
                test_logic_timer.start();
                while(test_logic_timer.getElapsedTime().asSeconds() <= (1 / 100.0)){}

                Game::systems().update();

                accumulator -= FIXED_TIMESTEP;
            }
            
            const double alpha = accumulator.asSeconds() / FIXED_TIMESTEP.asSeconds();


            frameRecorder.record(delta);
            if(frameRecorderTimer.getElapsedTime().asSeconds() > 1.0)
            {
                frameRecorderTimer.restart();
                Game::logger().log("AVG: " + std::to_string(1.0 / frameRecorder.getAverage().asSeconds()));
            }
            
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