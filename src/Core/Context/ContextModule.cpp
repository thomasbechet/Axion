#include <Core/Context/ContextModule.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Logger/LoggerModule.hpp>
#include <Core/Renderer/RendererModule.hpp>
#include <Core/Utility/ThreadPool.hpp>
#include <Core/Utility/TimeRecorder.hpp>
#include <Core/Scene/SceneModule.hpp>
#include <Core/Scene/System/SystemManager.hpp>
#include <Core/Window/WindowModule.hpp>
#include <Core/Input/InputModule.hpp>
#include <Core/Builder/BuilderModule.hpp>

#include <Core/Content/Component/Shape/QuadShapeComponent.hpp>
#include <Core/Content/Component/Shape/RectangleShapeComponent.hpp>
#include <Core/Content/Component/Shape/UVSphereShapeComponent.hpp>
#include <Core/Content/Component/BasicSpectatorComponent.hpp>
#include <Core/Content/Component/CameraComponent.hpp>
#include <Core/Content/Component/CustomShapeComponent.hpp>
#include <Core/Content/Component/DirectionalLightComponent.hpp>
#include <Core/Content/Component/ModelComponent.hpp>
#include <Core/Content/Component/PointLightComponent.hpp>
#include <Core/Content/Component/TransformComponent.hpp>
#include <Core/Content/System/BasicSpectatorSystem.hpp>
#include <Core/Content/System/BasicWindowSystem.hpp>
#include <Core/Content/System/RenderModeSystem.hpp>
#include <Core/Content/Asset/Material.hpp>
#include <Core/Content/Asset/Mesh.hpp>
#include <Core/Content/Asset/Model.hpp>
#include <Core/Content/Asset/Package.hpp>
#include <Core/Content/Asset/Scene.hpp>
#include <Core/Content/Asset/Shader.hpp>
#include <Core/Content/Asset/Texture.hpp>
#include <Core/Content/Asset/Template.hpp>

using namespace ax;

ContextModule::ContextModule(Path configurationFile)
{
    config.parse(configurationFile);
}

void ContextModule::initialize() noexcept
{
    //Record gamemodes
    

    //Record components
    Engine::builder().component.record<QuadShapeComponent>();
    Engine::builder().component.record<RectangleShapeComponent>();
    Engine::builder().component.record<UVSphereShapeComponent>();
    Engine::builder().component.record<BasicSpectatorComponent>();
    Engine::builder().component.record<CameraComponent>();
    Engine::builder().component.record<CustomShapeComponent>();
    Engine::builder().component.record<DirectionalLightComponent>();
    Engine::builder().component.record<ModelComponent>();
    Engine::builder().component.record<PointLightComponent>();
    Engine::builder().component.record<TransformComponent>();

    //Record systems
    Engine::builder().system.record<BasicSpectatorSystem>();
    Engine::builder().system.record<BasicWindowSystem>();
    Engine::builder().system.record<RenderModeSystem>();

    //Record assets
    ax::Engine::builder().asset.record<Material>();
    ax::Engine::builder().asset.record<Mesh>();
    ax::Engine::builder().asset.record<Model>();
    ax::Engine::builder().asset.record<Package>();
    ax::Engine::builder().asset.record<Scene>();
    ax::Engine::builder().asset.record<Shader>();
    ax::Engine::builder().asset.record<Texture>();
    ax::Engine::builder().asset.record<Template>();
}
void ContextModule::terminate() noexcept
{
    
}

bool ContextModule::isRunning() const noexcept
{
    return m_running;
}
void ContextModule::run() noexcept
{
    if(isRunning()) return;

    m_running = true;

    //Configure and start threadPool
    bool forceThread = Engine::context().config.getBoolean("System", "force_thread_count", false);
    unsigned threadCount = (forceThread) ? Engine::context().config.getUnsigned("System", "thread_count", 0) : 0;
    thread.start(threadCount);

    double fixed_timestep, maximum_timestep;
    if(Engine::context().config.getBoolean("Tick", "use_frequency", false))
    {   
        fixed_timestep = 1.0 / Engine::context().config.getDouble("Tick", "fixed_timestep_frequency", 50.0);
        maximum_timestep = 1.0 / Engine::context().config.getDouble("Tick", "maximum_timestep_frequency", 10.0);
    }
    else
    {
        fixed_timestep = Engine::context().config.getDouble("Tick", "fixed_timestep", 1.0 / 50.0);
        maximum_timestep = Engine::context().config.getDouble("Tick", "maximum_timestep", 1.0 / 10.0);
    }
    const Time FIXED_TIMESTEP = Time::make_seconds(fixed_timestep);
    const Time MAXIMUM_TIMESTEP = Time::make_seconds(maximum_timestep);
    
    //Tick recorder
    unsigned tick_measurement_count = Engine::context().config.getUnsigned("Tick", "tick_measurement_count", 10);
    TimeRecorder updateRecorder = TimeRecorder(tick_measurement_count);

    Timer displayInfoTimer;
    displayInfoTimer.start();

    //Starting clock
    m_timer.start();

    bool restart = true;
    while(restart)
    {
        restart = false;

        //Apply scene modification
        Engine::scene().next();

        //Engine loop
        Engine::scene().gamemode.get().onStart();
        Engine::scene().system.start();

        Time accumulator, delta;
        m_timer.restart();
        while(Engine::context().isRunning() && !Engine::scene().hasNext())
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
                Engine::scene().system.fixedUpdate();     
            }

            m_deltaTime = delta;
            //------> FRAME SYSTEMS UPDATE
            Engine::scene().system.update();
            
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

        Engine::scene().system.stop();
        Engine::scene().gamemode.get().onStop();
    
        if(Engine::scene().hasNext()) restart = true;
    }

    //Cleaning the scene
    ax::Engine::scene().system.removeAll();
    ax::Engine::scene().entity.destroyAll();

    //Stopping threads
    thread.stop();
}
void ContextModule::requestStop() noexcept
{
    m_running = false;
}

Time ContextModule::getDeltaTime() const noexcept
{
    return m_deltaTime;
}