#include <core/content/system/basic_spectator_system.hpp>

#include <core/input/input_module.hpp>
#include <core/math/math.hpp>
#include <core/context/context_module.hpp>

using namespace ax;

void basic_spectator_system::on_initialize()
{
    m_forward = &engine::input().add_button("basicspectator_forward");
    m_forward->bind(keyboard::w);
    m_backward = &engine::input().add_button("basicspectator_backward");
    m_backward->bind(keyboard::s);
    m_left = &engine::input().add_button("basicspectator_left");
    m_left->bind(keyboard::a);
    m_right = &engine::input().add_button("basicspectator_right");
    m_right->bind(keyboard::d);
    m_up = &engine::input().add_button("basicspectator_up");
    m_up->bind(keyboard::x);
    m_down = &engine::input().add_button("basicspectator_down");
    m_down->bind(keyboard::z);
    m_rotate_left = &engine::input().add_button("basicspectator_roll_left");
    m_rotate_left->bind(keyboard::e);
    m_rotate_right = &engine::input().add_button("basicspectator_roll_right");
    m_rotate_right->bind(keyboard::q);

    m_slow_mode = &engine::input().add_button("basicspectator_slowmode");
    m_slow_mode->bind(keyboard::left_control);
    m_fast_mode = &_engine::input().add_button("basicspectator_fastmode");
    m_fast_mode->bind(keyboard::left_shift);

    m_change_mode = &engine::input().add_button("basicspectator_changemode");
    m_change_mode->bind(keyboard::space);
    m_next_camera = &engine::input().add_button("basicspectator_next_camera");
    m_next_camera->bind(keyboard::n);

    m_look_x = &engine::input().add_axis("basicspectator_look_x");
    m_look_x->bind(mouse::axis::x);
    m_look_y = &engine::input().add_axis("basicspectator_look_y");
    m_look_y->bind(mouse::axis::y);

    m_zoom = &engine::input().add_axis("basicspectator_zoom");
    m_zoom->bind(mouse::axis::wheel_y);
}
void basic_spectator_system::on_update()
{
    if(m_next_camera->isJustPressed())
    {
        m_active++;
        if(m_active > m_components.size() - 1) m_active = 0;
    }

    if(m_active < m_components.size())
    {
        basic_spectator_component* component = m_components.at(m_active);

        float delta = engine::context().get_delta_time().as_seconds();

        vector2f look = vector2f(0.0f, 0.0f);
        look.x = m_look_x->delta();
        look.y = m_look_y->delta();
        float wheel_delta = m_zoom->delta();
        bool slow_mode = m_slow_mode->isPressed();
        bool fast_mode = m_fast_mode->isPressed();

        //Update mode
        if(m_change_mode->isJustPressed()) component->free_mode = !component->free_mode;

        //Translation
        vector3f direction = vector3f(0.0f, 0.0f, 0.0f);

        if(m_forward->is_pressed()) direction += component->transform.get_forward_vector();
        if(m_backward->is_pressed()) direction += component->transform.get_backward_vector();
        if(m_left->is_pressed()) direction += component->transform.get_left_vector();
        if(m_right->is_pressed()) direction += component->transform.get_right_vector();
        if(component->free_mode)
        {
            if(m_up->is_pressed()) direction += component->transform.get_up_vector();
            if(m_down->is_pressed()) direction += component->transform.get_down_vector();
        }
        else
        {
            if(m_up->is_pressed()) direction += vector3f::up;
            if(m_down->is_pressed()) direction += vector3f::down;
        }     
        direction.normalize();

        float speed = component->normal_speed;
        if(slow_mode) speed = component->slow_speed;
        else if(fast_mode) speed = component->fast_speed;

        component->transform.translate(direction * delta * speed);

        //Fov
        if(wheel_delta != 0.0f)
        {
            if(wheel_delta > 0.0f)
                component->camera.set_fov(component->camera.get_fov() - component->zoom_speed);
            else
                component->camera.set_fov(component->camera.get_fov() + component->zoom_speed);
        }
        
        //Rotation
        if(component->free_mode)
        {
            if(look.x != 0.0f) 
                component->transform.rotate(-math::radians(look.x) * component->rotation_sensibility, vector3f::up);
            if(look.y != 0.0f) 
                component->transform.rotate(math::radians(look.y) * component->rotation_sensibility, vector3f::right);
            if(m_rotate_left->isPressed())
                component->transform.rotate(math::radians(component->roll_speed) * delta, vector3f::forward);
            if(m_rotate_right->isPressed())
                component->transform.rotate(-math::radians(component->roll_speed) * delta, vector3f::forward);
        }
        else
        {
            if(look.x != 0.0f)
                component->yaw += look.x * component->rotation_sensibility;
            if(look.y != 0.0f)
                component->pitch += look.y * component->rotation_sensibility;

            if(component->pitch < -90.0f) component->pitch = -90.0f;
            if(component->pitch > 90.0f) component->pitch = 90.0f;

            component->transform.set_rotation(-math::radians(component->yaw), vector3f::up);
            component->transform.rotate(math::radians(component->pitch), vector3f::right);
        }
    }
}
void basic_spectator_system::on_terminate()
{
    engine::input().remove_button("basicspectator_forward");
    engine::input().remove_button("basicspectator_backward");
    engine::input().remove_button("basicspectator_left");
    engine::input().remove_button("basicspectator_right");
    engine::input().remove_button("basicspectator_up");
    engine::input().remove_button("basicspectator_down");
    engine::input().remove_button("basicspectator_roll_left");
    engine::input().remove_button("basicspectator_roll_right");
    engine::input().remove_button("basicspectator_slowmode");
    engine::input().remove_button("basicspectator_fastmode");
    engine::input().remove_button("basicspectator_changemode");
    engine::input().remove_button("basicspectator_next_camera");
    engine::input().remove_axis("basicspectator_look_x");
    engine::input().remove_axis("basicspectator_look_y");
    engine::input().remove_axis("basicspectator_zoom");
}

void basic_spectator_system::add(basic_spectator_component& component) noexcept
{
    m_components.push_back(&component);
}