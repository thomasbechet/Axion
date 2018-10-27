#include <OpenGL/Renderer/RendererGL.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Window/Window.hpp>

#include <GL/glew.h>

using namespace ax;

void RendererGL::initialize() noexcept
{
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
        Engine::interrupt("Failed to initialize GLEW");

    m_renderMode = RenderMode::Default;
    initializeRenderPass();
}
void RendererGL::terminate() noexcept
{
    terminateRenderPass();
}
void RendererGL::update(double alpha) noexcept
{
    renderRenderPass(alpha);
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
    if(m_renderMode != mode)
    {
        terminateRenderPass();

        m_renderMode = mode;
    
        initializeRenderPass();
    } 
}
RenderMode RendererGL::getRenderMode()
{
    return m_renderMode;
}

void RendererGL::initializeRenderPass() noexcept
{
    //Initialize new one
    switch(m_renderMode)
    {
        case RenderMode::Default:
            initializeDefault();
        break;
        case RenderMode::Wireframe:
            initializeWireframe();
        break;
        case RenderMode::Debug0:
            initializeDebug();
        break;
        case RenderMode::Debug1:
            initializeDebug();
        break;
        case RenderMode::Debug2:
            initializeDebug();
        break;
        default:
            initializeDefault();
        break;
    }
}
void RendererGL::renderRenderPass(double alpha) noexcept
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
void RendererGL::terminateRenderPass() noexcept
{
    switch(m_renderMode)
    {
        case RenderMode::Default:
            terminateDefault();
        break;
        case RenderMode::Wireframe:
            terminateWireframe();
        break;
        case RenderMode::Debug0:
            terminateDebug();
        break;
        case RenderMode::Debug1:
            terminateDebug();
        break;
        case RenderMode::Debug2:
            terminateDebug();
        break;
        default:
            terminateDefault();
        break;
    }
}