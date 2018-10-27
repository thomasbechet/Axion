#include <OpenGL/Renderer/RendererGL.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Window/Window.hpp>
#include <Core/Assets/AssetManager.hpp>

#include <GL/glew.h>

#include <iostream>

using namespace ax;

void RendererGL::initialize() noexcept
{
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
        Engine::interrupt("Failed to initialize GLEW");
}
void RendererGL::terminate() noexcept
{

}
void RendererGL::update(double alpha) noexcept
{
    switch(m_renderMode)
    {
        case RenderMode::Default:
            renderDefault(alpha);
        break;
        case RenderMode::Wireframe:
            renderWireframe(alpha);
        break;
        case RenderMode::Debug0:
            renderDebug(alpha, 0);
        break;
        case RenderMode::Debug1:
            renderDebug(alpha, 1);
        break;
        case RenderMode::Debug2:
            renderDebug(alpha, 2);
        break;
        default:
            renderDefault(alpha);
        break;
    }
}


//Viewport
void RendererGL::updateViewport() noexcept
{
    Vector2u windowSize = Engine::window().getSize();
    glViewport(0, 0, windowSize.x, windowSize.y);
}

//Rendermode
void RendererGL::setRenderMode(RenderMode mode)
{
    m_renderMode = mode;
}
RenderMode RendererGL::getRenderMode()
{
    return m_renderMode;
}