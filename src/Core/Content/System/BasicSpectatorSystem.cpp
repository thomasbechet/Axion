#include <Core/Content/System/BasicSpectatorSystem.hpp>

#include <Core/Input/InputModule.hpp>
#include <Core/Math/Math.hpp>
#include <Core/Context/ContextModule.hpp>

using namespace ax;

void BasicSpectatorSystem::onInitialize()
{
    m_forward = &Engine::input().addButton("basicspectator_forward");
    m_forward->bind(Keyboard::W);
    m_backward = &Engine::input().addButton("basicspectator_backward");
    m_backward->bind(Keyboard::S);
    m_left = &Engine::input().addButton("basicspectator_left");
    m_left->bind(Keyboard::A);
    m_right = &Engine::input().addButton("basicspectator_right");
    m_right->bind(Keyboard::D);
    m_up = &Engine::input().addButton("basicspectator_up");
    m_up->bind(Keyboard::X);
    m_down = &Engine::input().addButton("basicspectator_down");
    m_down->bind(Keyboard::Z);
    m_rotateLeft = &Engine::input().addButton("basicspectator_roll_left");
    m_rotateLeft->bind(Keyboard::E);
    m_rotateRight = &Engine::input().addButton("basicspectator_roll_right");
    m_rotateRight->bind(Keyboard::Q);

    m_slowMode = &Engine::input().addButton("basicspectator_slowmode");
    m_slowMode->bind(Keyboard::LeftControl);
    m_fastMode = &Engine::input().addButton("basicspectator_fastmode");
    m_fastMode->bind(Keyboard::LeftShift);

    m_changeMode = &Engine::input().addButton("basicspectator_changemode");
    m_changeMode->bind(Keyboard::Space);
    m_nextCamera = &Engine::input().addButton("basicspectator_next_camera");
    m_nextCamera->bind(Keyboard::N);

    m_lookX = &Engine::input().addAxis("basicspectator_look_x");
    m_lookX->bind(Mouse::Axis::X);
    m_lookY = &Engine::input().addAxis("basicspectator_look_y");
    m_lookY->bind(Mouse::Axis::Y);

    m_zoom = &Engine::input().addAxis("basicspectator_zoom");
    m_zoom->bind(Mouse::Axis::WheelY);
}
void BasicSpectatorSystem::onUpdate()
{
    if(m_nextCamera->isJustPressed())
    {
        m_active++;
        if(m_active > m_components.size() - 1) m_active = 0;
    }

    if(m_active < m_components.size())
    {
        BasicSpectatorComponent* component = m_components.at(m_active);

        float delta = Engine::context().getDeltaTime().asSeconds();

        Vector2f look = Vector2f(0.0f, 0.0f);
        look.x = m_lookX->delta();
        look.y = m_lookY->delta();
        float wheelDelta = m_zoom->delta();
        bool slowMode = m_slowMode->isPressed();
        bool fastMode = m_fastMode->isPressed();

        //Update mode
        if(m_changeMode->isJustPressed()) component->freeMode = !component->freeMode;

        //Translation
        Vector3f direction = Vector3f(0.0f, 0.0f, 0.0f);

        if(m_forward->isPressed()) direction += component->transform.getForwardVector();
        if(m_backward->isPressed()) direction += component->transform.getBackwardVector();
        if(m_left->isPressed()) direction += component->transform.getLeftVector();
        if(m_right->isPressed()) direction += component->transform.getRightVector();
        if(component->freeMode)
        {
            if(m_up->isPressed()) direction += component->transform.getUpVector();
            if(m_down->isPressed()) direction += component->transform.getDownVector();
        }
        else
        {
            if(m_up->isPressed()) direction += Vector3f::up;
            if(m_down->isPressed()) direction += Vector3f::down;
        }     
        direction.normalize();

        float speed = component->normalSpeed;
        if(slowMode) speed = component->slowSpeed;
        else if(fastMode) speed = component->fastSpeed;

        component->transform.translate(direction * delta * speed);

        //Fov
        if(wheelDelta != 0.0f)
        {
            if(wheelDelta > 0.0f)
                component->camera.setFov(component->camera.getFov() - component->zoomSpeed);
            else
                component->camera.setFov(component->camera.getFov() + component->zoomSpeed);
        }
        
        //Rotation
        if(component->freeMode)
        {
            if(look.x != 0.0f) 
                component->transform.rotate(-radians(look.x) * component->rotationSensibility, Vector3f::up);
            if(look.y != 0.0f) 
                component->transform.rotate(radians(look.y) * component->rotationSensibility, Vector3f::right);
            if(m_rotateLeft->isPressed())
                component->transform.rotate(radians(component->rollSpeed) * delta, Vector3f::forward);
            if(m_rotateRight->isPressed())
                component->transform.rotate(-radians(component->rollSpeed) * delta, Vector3f::forward);
        }
        else
        {
            if(look.x != 0.0f)
                component->yaw += look.x * component->rotationSensibility;
            if(look.y != 0.0f)
                component->pitch += look.y * component->rotationSensibility;

            if(component->pitch < -90.0f) component->pitch = -90.0f;
            if(component->pitch > 90.0f) component->pitch = 90.0f;

            component->transform.setRotation(-radians(component->yaw), Vector3f::up);
            component->transform.rotate(radians(component->pitch), Vector3f::right);
        }
    }
}
void BasicSpectatorSystem::onTerminate()
{
    Engine::input().removeButton("basicspectator_forward");
    Engine::input().removeButton("basicspectator_backward");
    Engine::input().removeButton("basicspectator_left");
    Engine::input().removeButton("basicspectator_right");
    Engine::input().removeButton("basicspectator_up");
    Engine::input().removeButton("basicspectator_down");
    Engine::input().removeButton("basicspectator_roll_left");
    Engine::input().removeButton("basicspectator_roll_right");
    Engine::input().removeButton("basicspectator_slowmode");
    Engine::input().removeButton("basicspectator_fastmode");
    Engine::input().removeButton("basicspectator_changemode");
    Engine::input().removeButton("basicspectator_next_camera");
    Engine::input().removeAxis("basicspectator_look_x");
    Engine::input().removeAxis("basicspectator_look_y");
    Engine::input().removeAxis("basicspectator_zoom");
}

void BasicSpectatorSystem::add(BasicSpectatorComponent& component) noexcept
{
    m_components.push_back(&component);
}