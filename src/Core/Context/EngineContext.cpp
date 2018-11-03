#include <Core/Context/EngineContext.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/System/SystemManager.hpp>
#include <Core/Logger/Logger.hpp>
#include <Core/Renderer/Renderer.hpp>
#include <Core/Utility/ThreadPool.hpp>
#include <Core/Utility/TimeRecorder.hpp>
#include <Core/World/World.hpp>
#include <Core/Window/Window.hpp>
#include <Core/Input/Input.hpp>

using namespace ax;

ConfigParser& EngineContext::config() noexcept
{
    return m_configParser;
}

bool EngineContext::isRunning() const noexcept
{
    return m_running;
}
void EngineContext::run() noexcept
{
    if(isRunning()) return;

    m_running = true;

    //Configure and start threadPool
    bool forceThread = Engine::context().config().getBoolean("System", "force_thread_count", false);
    unsigned threadCount = (forceThread) ? Engine::context().config().getUnsigned("System", "thread_count", 0) : 0;
    Engine::threads().start(threadCount);

    double fixed_timestep, maximum_timestep;
    if(Engine::context().config().getBoolean("Tick", "use_frequency", false))
    {   
        fixed_timestep = 1.0 / Engine::context().config().getDouble("Tick", "fixed_timestep_frequency", 50.0);
        maximum_timestep = 1.0 / Engine::context().config().getDouble("Tick", "maximum_timestep_frequency", 10.0);
    }
    else
    {
        fixed_timestep = Engine::context().config().getDouble("Tick", "fixed_timestep", 1.0 / 50.0);
        maximum_timestep = Engine::context().config().getDouble("Tick", "maximum_timestep", 1.0 / 10.0);
    }
    const Time FIXED_TIMESTEP = Time::make_seconds(fixed_timestep);
    const Time MAXIMUM_TIMESTEP = Time::make_seconds(maximum_timestep);
    
    //Tick recorder
    unsigned tick_measurement_count = Engine::context().config().getUnsigned("Tick", "tick_measurement_count", 10);
    TimeRecorder updateRecorder = TimeRecorder(tick_measurement_count);

    Timer displayInfoTimer;
    displayInfoTimer.start();

    //Starting clock
    m_timer.start();

    bool restart = true;
    while(restart)
    {
        restart = false;

        //Apply gamemode modification
        if(Engine::world().hasNextGameMode())
            Engine::world().nextGameMode();

        //Engine loop
        Engine::world().getGameMode().onStart();
        Engine::systems().start();

        Time accumulator, delta;
        m_timer.restart();
        while(Engine::context().isRunning() && !Engine::world().hasNextGameMode())
        {
            delta = m_timer.getElapsedTime();
            updateRecorder.record(delta);
            m_timer.restart();

            if(delta > MAXIMUM_TIMESTEP)
                delta = MAXIMUM_TIMESTEP; //slowing down

            accumulator += delta;

            //------> PROCESS WINDOW
            Engine::window().update();
            //------> PROCESS INPUTS
            Engine::input().update();
            Engine::input().updateInputs();

            m_deltaTime = FIXED_TIMESTEP;
            while(accumulator >= FIXED_TIMESTEP)
            {   
                accumulator -= FIXED_TIMESTEP;

                //-----> PHYSIC UPDATE
                //-----> FIXED SYSTEMS UPDATE
                Engine::systems().fixedUpdate();     
            }

            m_deltaTime = delta;
            //------> FRAME SYSTEMS UPDATE
            Engine::systems().update();
            
            
            const double alpha = accumulator.asSeconds() / FIXED_TIMESTEP.asSeconds();

            //------> RENDER
            Engine::renderer().update(alpha);
            //------> SWAP BUFFERS
            Engine::window().swapBuffers();

            if(displayInfoTimer.getElapsedTime().asSeconds() > 1.0)
            {
                displayInfoTimer.restart();
                Engine::logger().log("Time: " + std::to_string(updateRecorder.getAverage().asMilliseconds()));
            }
        }

        Engine::systems().stop();
        Engine::world().getGameMode().onStop();
    
        if(Engine::world().hasNextGameMode()) restart = true;
    }

    //Removing all systems
    ax::Engine::systems().removeAll();

    //Stopping threads
    Engine::threads().stop();
}
void EngineContext::requestStop() noexcept
{
    m_running = false;
}

Time EngineContext::getDeltaTime() const noexcept
{
    return m_deltaTime;
}