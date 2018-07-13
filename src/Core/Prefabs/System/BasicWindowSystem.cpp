#include <Core/Prefabs/System/BasicWindowSystem.hpp>

#include <Core/Context/Game.hpp>
#include <Core/Context/GameContext.hpp>
#include <Core/Input/Input.hpp>
#include <Core/Window/Window.hpp>

using namespace ax;

std::string BasicWindowSystem::name() noexcept
{
    return "BasicWindowSystem";
}

void BasicWindowSystem::onInitialize()
{
    m_fullscreenButton = &Game::input().addButton("basicwindow_fullscreen");
    m_fullscreenButton->bind(Keyboard::F11);
    m_borderlessButton = &Game::input().addButton("basicwindow_borderless");
    m_borderlessButton->bind(Keyboard::F12);
    m_closeButton = &Game::input().addButton("basicwindow_close");
    m_closeButton->bind(Keyboard::Escape);
}
void BasicWindowSystem::onUpdate()
{
    if(m_fullscreenButton->isJustPressed())
    {
        if(Game::window().getMode() == WindowMode::Windowed)
            Game::window().setMode(WindowMode::Fullscreen);
        else
            Game::window().setMode(WindowMode::Windowed);
    }
    else if(m_borderlessButton->isJustPressed())
    {
        if(Game::window().getMode() == WindowMode::Windowed)
            Game::window().setMode(WindowMode::Borderless);
        else
            Game::window().setMode(WindowMode::Windowed);
    }
    else if(m_closeButton->isJustPressed() || Game::window().shouldClose())
        Game::engine().stop();
}
void BasicWindowSystem::onTerminate()
{
    Game::input().removeButton("basicwindow_fullscreen");
    Game::input().removeButton("basicwindow_borderless");
    Game::input().removeButton("basicwindow_close");
}