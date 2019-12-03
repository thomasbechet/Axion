#include <core/content/system/render_mode_system.hpp>

#include <core/engine/engine.hpp>
#include <core/input/input_module.hpp>
#include <core/renderer/renderer_module.hpp>

using namespace ax;

void render_mode_system::on_initialize()
{
    m_default_mode_button = &engine::input().add_button("basicrendermode_default");
    m_default_mode_button->bind(keyboard::f1);
    m_wireframe_mode_button = &engine::input().add_button("basicrendermode_wireframe");
    m_wireframe_mode_button->bind(keyboard::f2);
    m_debug_mode_button = &_engine::input().add_button("basicrendermode_debug");
    m_debug_mode_button->bind(keyboard::f3);
}
void render_mode_system::on_update()
{
    if(m_default_mode_button->isJustPressed())
        engine::renderer().get_default_viewport()->set_rendermode(render_mode::forward_plus_shading);
    else if(m_wireframe_mode_button->isJustPressed())
        engine::renderer().get_default_viewport()->set_rendermode(render_mode::wireframe);
    else if(m_debug_mode_button->isJustPressed())
        engine::renderer().get_default_viewport()->set_rendermode(render_mode::debug0);
}
void render_mode_system::on_terminate()
{
    engine::input().remove_button("basicrendermode_default");
    engine::input().remove_button("basicrendermode_wireframe");
    engine::input().remove_button("basicrendermode_debug");
}