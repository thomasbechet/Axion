#include <Core/Prefab/System/BasicWindowSystem.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Context/EngineContext.hpp>
#include <Core/Window/Window.hpp>
#include <Core/Input/Input.hpp>

using namespace ax;

void BasicWindowSystem::onInitialize()
{
    m_fullscreenButton = &Engine::input().addButton("basicwindow_fullscreen");
    m_fullscreenButton->bind(Keyboard::F11);
    m_borderlessButton = &Engine::input().addButton("basicwindow_borderless");
    m_borderlessButton->bind(Keyboard::F12);
    m_closeButton = &Engine::input().addButton("basicwindow_close");
    m_closeButton->bind(Keyboard::Escape);
}
void BasicWindowSystem::onUpdate()
{
    if(m_fullscreenButton->isJustPressed())
    {
        if(Engine::window().getMode() == WindowMode::Windowed)
            Engine::window().setMode(WindowMode::Fullscreen);
        else
            Engine::window().setMode(WindowMode::Windowed);
    }
    else if(m_borderlessButton->isJustPressed())
    {
        if(Engine::window().getMode() == WindowMode::Windowed)
            Engine::window().setMode(WindowMode::Borderless);
        else
            Engine::window().setMode(WindowMode::Windowed);
    }
    else if(m_closeButton->isJustPressed() || Engine::window().shouldClose())
        Engine::context().requestStop();
}
void BasicWindowSystem::onTerminate()
{
    Engine::input().removeButton("basicwindow_fullscreen");
    Engine::input().removeButton("basicwindow_borderless");
    Engine::input().removeButton("basicwindow_close");
}