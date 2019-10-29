#include <Core/Prefab/System/RenderModeSystem.hpp>

#include <Core/Input/InputModule.hpp>
#include <Core/Renderer/RendererModule.hpp>

using namespace ax;

void RenderModeSystem::onInitialize()
{
    m_defaultModeButton = &Engine::input().addButton("basicrendermode_default");
    m_defaultModeButton->bind(Keyboard::F1);
    m_wireframeModeButton = &Engine::input().addButton("basicrendermode_wireframe");
    m_wireframeModeButton->bind(Keyboard::F2);
    m_debugModeButton = &Engine::input().addButton("basicrendermode_debug");
    m_debugModeButton->bind(Keyboard::F3);
}
void RenderModeSystem::onUpdate()
{
    if(m_defaultModeButton->isJustPressed())
        Engine::renderer().getDefaultViewport()->setRendermode(RenderMode::ForwardPlusShading);
    else if(m_wireframeModeButton->isJustPressed())
        Engine::renderer().getDefaultViewport()->setRendermode(RenderMode::Wireframe);
    else if(m_debugModeButton->isJustPressed())
        Engine::renderer().getDefaultViewport()->setRendermode(RenderMode::Debug0);
}
void RenderModeSystem::onTerminate()
{
    Engine::input().removeButton("basicrendermode_default");
    Engine::input().removeButton("basicrendermode_wireframe");
    Engine::input().removeButton("basicrendermode_debug");
}