#include <Core/Context/GameContext.hpp>

#include <Core/Context/Game.hpp>
#include <Core/System/SystemManager.hpp>
#include <Core/Logger/Logger.hpp>
#include <Core/Renderer/Renderer.hpp>
#include <Core/Utility/ThreadPool.hpp>
#include <Core/Utility/TimeRecorder.hpp>
#include <Core/World/World.hpp>
#include <Core/Window/Window.hpp>
#include <Core/Input/Input.hpp>

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

    //Initializes engine
    Game::window().initialize();
    Game::input().initialize();
    Game::renderer().initialize();

    //Configure and start threadPool
    bool forceThread = Game::engine().config().getBoolean("System", "force_thread_count", false);
    unsigned threadCount = (forceThread) ? Game::engine().config().getUnsigned("System", "thread_count", 0) : 0;
    Game::threads().start(threadCount);

    double fixed_timestep, maximum_timestep;
    if(Game::engine().config().getBoolean("Tick", "use_frequency", false))
    {   
        fixed_timestep = 1.0 / Game::engine().config().getDouble("Tick", "fixed_timestep_frequency", 50.0);
        maximum_timestep = 1.0 / Game::engine().config().getDouble("Tick", "maximum_timestep_frequency", 10.0);
    }
    else
    {
        fixed_timestep = Game::engine().config().getDouble("Tick", "fixed_timestep", 1.0 / 50.0);
        maximum_timestep = Game::engine().config().getDouble("Tick", "maximum_timestep", 1.0 / 10.0);
    }
    const Time FIXED_TIMESTEP = Time::make_seconds(fixed_timestep);
    const Time MAXIMUM_TIMESTEP = Time::make_seconds(maximum_timestep);
    
    //Tick recorder
    unsigned average_update_count = Game::engine().config().getUnsigned("Tick", "average_update_count", 10);
    TimeRecorder updateRecorder = TimeRecorder(average_update_count);

    Timer displayInfoTimer;
    displayInfoTimer.start();

    //Starting clock
    m_timer.start();

    bool restart = true;
    while(restart)
    {
        restart = false;

        //Apply gamemode modification
        if(Game::world().hasNextGameMode())
            Game::world().nextGameMode();

        //Game loop
        Game::world().getGameMode().onStart();
        Game::systems().start();

        Time accumulator, delta;
        m_timer.restart();
        while(Game::engine().isRunning() && !Game::world().hasNextGameMode())
        {
            delta = m_timer.getElapsedTime();
            updateRecorder.record(delta);
            m_timer.restart();

            if(delta > MAXIMUM_TIMESTEP)
                delta = MAXIMUM_TIMESTEP; //slowing down

            accumulator += delta;

            //------> PROCESS WINDOW
            Game::window().update();
            //------> PROCESS INPUTS
            Game::input().update();
            Game::input().updateInputs();

            m_deltaTime = FIXED_TIMESTEP;
            while(accumulator >= FIXED_TIMESTEP)
            {   
                accumulator -= FIXED_TIMESTEP;

                //-----> PHYSIC UPDATE
                //-----> FIXED SYSTEMS UPDATE
                Game::systems().fixedUpdate();     
            }

            m_deltaTime = delta;
            //------> FRAME SYSTEMS UPDATE
            Game::systems().update();
            
            const double alpha = accumulator.asSeconds() / FIXED_TIMESTEP.asSeconds();

            //------> RENDER
            Game::renderer().update(alpha);
            //------> SWAP BUFFERS
            Game::window().swapBuffers();

            if(displayInfoTimer.getElapsedTime().asSeconds() > 1.0)
            {
                displayInfoTimer.restart();
                Game::logger().log("FPS: " + std::to_string(1.0 / updateRecorder.getAverage().asSeconds()));
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


    //Terminates engine
    Game::renderer().terminate();
    Game::input().terminate();
    Game::window().terminate();
}
void GameContext::stop() noexcept
{
    m_running = false;
}

Time GameContext::getDeltaTime() const noexcept
{
    return m_deltaTime;
}