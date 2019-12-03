#include <core/context/context_module.hpp>

#include <core/engine/engine.hpp>
#include <core/logger/logger_module.hpp>
#include <core/renderer/renderer_module.hpp>
#include <core/utility/thread_pool.hpp>
#include <core/utility/time_recorder.hpp>
#include <core/scene/scene_module.hpp>
#include <core/scene/system/_system_manager.hpp>
#include <core/window/window_module.hpp>
#include <core/input/input_module.hpp>
#include <core/builder/builder_module.hpp>

#include <core/content/component/shape/_quad_shape_component.hpp>
#include <core/content/component/shape/_rectangle_shape_component.hpp>
#include <core/content/component/shape/uv_sphere_shape_component.hpp>
#include <core/content/component/basic_spectator_component.hpp>
#include <core/content/component/camera_component.hpp>
#include <core/content/component/custom_shape_component.hpp>
#include <core/content/component/directional_light_component.hpp>
#include <core/content/component/model_component.hpp>
#include <core/content/component/point_light_component.hpp>
#include <core/content/component/transform_component.hpp>
#include <core/content/system/basic_spectator_system.hpp>
#include <core/content/system/basic_window_system.hpp>
#include <core/content/system/render_mode_system.hpp>
#include <core/content/asset/material_asset.hpp>
#include <core/content/asset/mesh_asset.hpp>
#include <core/content/asset/model_asset.hpp>
#include <core/content/asset/package_asset.hpp>
#include <core/content/asset/scene_asset.hpp>
#include <core/content/asset/shader_asset.hpp>
#include <core/content/asset/texture_asset.hpp>
#include <core/content/asset/template_asset.hpp>

using namespace ax;
using namespace ax::detail;

context_module::context_module(path configuration_file)
{
    config.parse(configuration_file);
}

void context_module::initialize() noexcept
{
    //Record gamemodes
    

    //Record components
    engine::builder().component.record<quad_shape_component>();
    engine::builder().component.record<rectangle_shape_component>();
    engine::builder().component.record<uv_sphere_shape_component>();
    engine::builder().component.record<basic_spectator_component>();
    engine::builder().component.record<camera_component>();
    engine::builder().component.record<custom_shape_component>();
    engine::builder().component.record<directional_light_component>();
    engine::builder().component.record<model_component>();
    engine::builder().component.record<point_light_component>();
    engine::builder().component.record<transform_component>();

    //Record systems
    engine::builder().system.record<basic_spectator_system>();
    engine::builder().system.record<basic_window_system>();
    engine::builder().system.record<render_mode_system>();

    //Record assets
    engine::builder().asset.record<material_asset>();
    engine::builder().asset.record<mesh_asset>();
    engine::builder().asset.record<model_asset>();
    engine::builder().asset.record<package_asset>();
    engine::builder().asset.record<scene_asset>();
    engine::builder().asset.record<shader_asset>();
    engine::builder().asset.record<texture_asset>();
    engine::builder().asset.record<template_asset>();
}
void context_module::terminate() noexcept
{
    
}

bool context_module::is_running() const noexcept
{
    return m_running;
}
void context_module::run() noexcept
{
    if(is_running()) return;

    m_running = true;

    //Configure and start thread_pool
    bool force_thread = engine::context().config.get_boolean("system", "force_thread_count", false);
    unsigned thread_count = (force_thread) ? engine::context().config.get_unsigned("system", "thread_count", 0) : 0;
    thread.start(thread_count);

    double fixed_timestep, maximum_timestep;
    if(engine::context().config.get_boolean("tick", "use_frequency", false))
    {   
        fixed_timestep = 1.0 / engine::context().config.get_double("tick", "fixed_timestep_frequency", 50.0);
        maximum_timestep = 1.0 / engine::context().config.get_double("tick", "maximum_timestep_frequency", 10.0);
    }
    else
    {
        fixed_timestep = engine::context().config.get_double("tick", "fixed_timestep", 1.0 / 50.0);
        maximum_timestep = engine::context().config.get_double("tick", "maximum_timestep", 1.0 / 10.0);
    }
    const time FIXED_TIMESTEP = time::make_seconds(fixed_timestep);
    const time MAXIMUM_TIMESTEP = time::make_seconds(maximum_timestep);
    
    //Tick recorder
    unsigned tick_measurement_count = engine::context().config.get_unsigned("tick", "tick_measurement_count", 10);
    time_recorder update_recorder = time_recorder(tick_measurement_count);

    timer display_info_timer;
    display_info_timer.start();

    //Starting clock
    m_timer.start();

    bool restart = true;
    while(restart)
    {
        restart = false;

        //Apply scene modification
        engine::scene().next();

        //Engine loop
        engine::scene().gamemode.get().on_start();
        engine::scene().system.start();

        time accumulator, delta;
        m_timer.restart();
        while(engine::context().is_running() && !engine::scene().has_next())
        {
            delta = m_timer.get_elapsed_time();
            update_recorder.record(delta);
            m_timer.restart();

            if(delta > MAXIMUM_TIMESTEP)
                delta = MAXIMUM_TIMESTEP; //slowing down

            accumulator += delta;

            //------> PROCESS WINDOW
            engine::window().update();
            //------> PROCESS INPUTS
            engine::input().update();
            engine::input().update_inputs();

            m_delta_time = FIXED_TIMESTEP;
            while(accumulator >= FIXED_TIMESTEP)
            {   
                accumulator -= FIXED_TIMESTEP;

                //-----> PHYSIC UPDATE
                //-----> FIXED SYSTEMS UPDATE
                engine::scene().system.fixed_update();     
            }

            m_delta_time = delta;
            //------> FRAME SYSTEMS UPDATE
            engine::scene().system.update();
            
            const double alpha = accumulator.as_seconds() / fixed_timestep.as_seconds();

            //------> RENDER
            engine::renderer().update(alpha);
            //------> SWAP BUFFERS
            engine::window().swap_buffers();

            if(display_info_timer.get_elapsed_time().as_seconds() > 1.0)
            {
                display_info_timer.restart();
                Engine::logger().log("Time: " + std::to_string(update_recorder.get_average().as_milli_seconds()));
            }
        }

        engine::scene().system.stop();
        engine::scene().gamemode.get().on_stop();
    
        if(engine::scene().has_next()) restart = true;
    }

    //Cleaning the scene
    engine::scene().system.remove_all();
    engine::scene().entity.destroy_all();

    //Stopping threads
    thread.stop();
}
void context_module::request_stop() noexcept
{
    m_running = false;
}

time context_module::get_delta_time() const noexcept
{
    return m_delta_time;
}