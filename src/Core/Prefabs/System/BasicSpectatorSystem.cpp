#include <Core/Prefabs/System/BasicSpectatorSystem.hpp>

#include <Core/Input/Input.hpp>
#include <Core/Math/Math.hpp>
#include <Core/World/Component/ComponentIterator.hpp>
#include <Core/Context/EngineContext.hpp>

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

    m_lookX = &Engine::input().addAxis("basicspectator_look_x");
    m_lookX->bind(Mouse::Axis::X);
    m_lookY = &Engine::input().addAxis("basicspectator_look_y");
    m_lookY->bind(Mouse::Axis::Y);

    m_zoom = &Engine::input().addAxis("basicspectator_zoom");
    m_zoom->bind(Mouse::Axis::WheelY);

    m_list = &Engine::world().components().getList<BasicSpectatorComponent>();
}
void BasicSpectatorSystem::onUpdate()
{
    float delta = Engine::context().getDeltaTime().asSeconds();

    Vector2f look = Vector2f(0.0f, 0.0f);
    look.x = m_lookX->delta();
    look.y = m_lookY->delta();
    float wheelDelta = m_zoom->delta();
    bool slowMode = m_slowMode->isPressed();
    bool fastMode = m_fastMode->isPressed();

    auto it = m_list->iterator();
    while(it.next())
    {
        //Update mode
        if(m_changeMode->isJustPressed()) it->freeMode = !it->freeMode;

        //Translation
        Vector3f direction = Vector3f(0.0f, 0.0f, 0.0f);

        if(m_forward->isPressed()) direction += it->transform.getForwardVector();
        if(m_backward->isPressed()) direction += it->transform.getBackwardVector();
        if(m_left->isPressed()) direction += it->transform.getLeftVector();
        if(m_right->isPressed()) direction += it->transform.getRightVector();
        if(it->freeMode)
        {
            if(m_up->isPressed()) direction += it->transform.getUpVector();
            if(m_down->isPressed()) direction += it->transform.getDownVector();
        }
        else
        {
            if(m_up->isPressed()) direction += Vector3f::up;
            if(m_down->isPressed()) direction += Vector3f::down;
        }     
        direction.normalize();

        float speed = it->normalSpeed;
        if(slowMode) speed = it->slowSpeed;
        else if(fastMode) speed = it->fastSpeed;

        it->transform.translate(direction * delta * speed);

        //Fov
        if(wheelDelta != 0.0f)
        {
            if(wheelDelta > 0.0f)
                it->camera.setFov(it->camera.getFov() - it->zoomSpeed);
            else
                it->camera.setFov(it->camera.getFov() + it->zoomSpeed);
        }
        
        //Rotation
        if(it->freeMode)
        {
            if(look.x != 0.0f) 
                it->transform.rotate(-radians(look.x) * it->rotationSensibility, Vector3f::up);
            if(look.y != 0.0f) 
                it->transform.rotate(radians(look.y) * it->rotationSensibility, Vector3f::right);
            if(m_rotateLeft->isPressed())
                it->transform.rotate(radians(it->rollSpeed) * delta, Vector3f::forward);
            if(m_rotateRight->isPressed())
                it->transform.rotate(-radians(it->rollSpeed) * delta, Vector3f::forward);
        }
        else
        {
            if(look.x != 0.0f)
                it->yaw += look.x * it->rotationSensibility;
            if(look.y != 0.0f)
                it->pitch += look.y * it->rotationSensibility;

            if(it->pitch < -90.0f) it->pitch = -90.0f;
            if(it->pitch > 90.0f) it->pitch = 90.0f;

            it->transform.setRotation(-radians(it->yaw), Vector3f::up);
            it->transform.rotate(radians(it->pitch), Vector3f::right);
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
    Engine::input().removeAxis("basicspectator_look_x");
    Engine::input().removeAxis("basicspectator_look_y");
    Engine::input().removeAxis("basicspectator_zoom");
}