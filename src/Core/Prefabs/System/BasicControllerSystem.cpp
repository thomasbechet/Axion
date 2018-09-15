#include <Core/Prefabs/System/BasicControllerSystem.hpp>

#include <Core/Input/Input.hpp>
#include <Core/Math/Math.hpp>
#include <Core/World/Component/ComponentIterator.hpp>
#include <Core/Context/EngineContext.hpp>

using namespace ax;

std::string BasicControllerSystem::name() noexcept
{
    return "BasicController";
}

void BasicControllerSystem::onInitialize()
{
    m_reset = &Engine::input().addButton("basiccontroller_reset");
    m_reset->bind(Keyboard::Space);
    m_forward = &Engine::input().addButton("basiccontroller_forward");
    m_forward->bind(Keyboard::W);
    m_backward = &Engine::input().addButton("basiccontroller_backward");
    m_backward->bind(Keyboard::S);
    m_left = &Engine::input().addButton("basiccontroller_left");
    m_left->bind(Keyboard::A);
    m_right = &Engine::input().addButton("basiccontroller_right");
    m_right->bind(Keyboard::D);
    m_up = &Engine::input().addButton("basiccontroller_up");
    m_up->bind(Keyboard::X);
    m_down = &Engine::input().addButton("basiccontroller_down");
    m_down->bind(Keyboard::Z);
    m_rotateLeft = &Engine::input().addButton("basiccontroller_rotate_left");
    m_rotateLeft->bind(Keyboard::E);
    m_rotateRight = &Engine::input().addButton("basiccontroller_rotate_right");
    m_rotateRight->bind(Keyboard::Q);

    m_lookX = &Engine::input().addAxis("basiccontroller_look_x");
    m_lookX->bind(Mouse::Axis::X);
    m_lookY = &Engine::input().addAxis("basiccontroller_look_y");
    m_lookY->bind(Mouse::Axis::Y);

    m_list = &Engine::world().components().getList<BasicControllerComponent>();
}
void BasicControllerSystem::onUpdate()
{
    Vector3f direction = Vector3f(0.0f, 0.0f, 0.0f);
    Vector2f look = Vector2f(0.0f, 0.0f);

    if(m_forward->isPressed()) direction += Vector3f::forward;
    if(m_backward->isPressed()) direction += Vector3f::backward;
    if(m_left->isPressed()) direction += Vector3f::left;
    if(m_right->isPressed()) direction += Vector3f::right;
    if(m_up->isPressed()) direction += Vector3f::up;
    if(m_down->isPressed()) direction += Vector3f::down;
    direction.normalize();

    look.x = m_lookX->delta();
    look.y = m_lookY->delta();

    float delta = Engine::context().getDeltaTime().asSeconds();

    auto it = m_list->iterator();
    while(it.next())
    {
        it->transform.translate(direction * it->speed * delta);
        if(look.x != 0.0f) 
            it->transform.rotate(radians(look.x), it->transform.getUpVector());
        if(look.y != 0.0f) 
            it->transform.rotate(radians(look.y), it->transform.getRightVector());

        if(Engine::input().isButtonPressed(Keyboard::Space))
            it->transform.setRotation(Quaternionf(0.0f, Vector3f::up));
    }
}
void BasicControllerSystem::onTerminate()
{
    Engine::input().removeButton("basiccontroller_reset");
    Engine::input().removeButton("basiccontroller_forward");
    Engine::input().removeButton("basiccontroller_backward");
    Engine::input().removeButton("basiccontroller_left");
    Engine::input().removeButton("basiccontroller_right");
    Engine::input().removeButton("basiccontroller_up");
    Engine::input().removeButton("basiccontroller_down");
    Engine::input().removeButton("basiccontroller_rotate_left");
    Engine::input().removeButton("basiccontroller_rotate_right");
    Engine::input().removeAxis("basiccontroller_look_x");
    Engine::input().removeAxis("basiccontroller_look_y");
}