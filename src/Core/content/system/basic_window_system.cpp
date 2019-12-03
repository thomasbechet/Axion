#include <core/content/system/basic_window_system.hpp>

#include <Core/Engine/Engine.hpp>
#include <core/context/context_module.hpp>
#include <core/window/window_module.hpp>
#include <core/input/input_module.hpp>

using namespace ax;

void basic_window_system::on_initialize()
{
    m_fullscreen_button = &engine::input().add_button("basicwindow_fullscreen");
    m_fullscreen_button->bind(keyboard::f11);
    m_borderless_button = &engine::input().add_button("basicwindow_borderless");
    m_borderless_button->bind(keyboard::f10);
    m_close_button = &engine::input().add_button("basicwindow_close");
    m_close_button->bind(keyboard::escape);
    m_vsync_button = &engine::input().add_button("basicwindow_vsync");
    m_vsync_button->bind(keyboard::f9);
}
void basic_window_system::on_update()
{
    if(m_fullscreen_button->is_just_pressed())
    {
        if(_engine::window().get_mode() == window_mode::windowed)
            engine::window().set_mode(_window_mode::fullscreen);
        else
            Engine::window().setMode(window_mode::windowed);
    }
    else if(m_borderless_button->is_just_pressed())
    {
        if(_engine::window().get_mode() == window_mode::windowed)
            engine::window().set_mode(window_mode::borderless);
        else
            Engine::window().setMode(window_mode::windowed);
    }
    else if(m_close_button->is_just_pressed() || engine::window().should_close())
    {
        engine::context().request_stop();
    }
    else if(m_vsync_button->is_just_pressed())
    {
        engine::window().set_vertical_sync(!engine::window().get_vertical_sync());
    }
}
void basic_window_system::on_terminate()
{
    engine::input().remove_button("basicwindow_fullscreen");
    engine::input().remove_button("basicwindow_borderless");
    engine::input().remove_button("basicwindow_close");
    engine::input().remove_button("basicwindow_vsync");
}