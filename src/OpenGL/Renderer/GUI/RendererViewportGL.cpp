#include <OpenGL/Renderer/GUI/RendererViewportGL.hpp>

#include <OpenGL/Renderer/RendererGL.hpp>
#include <OpenGL/Renderer/RenderPass/ForwardPlusPass.hpp>
#include <OpenGL/Renderer/RenderPass/WireframePass.hpp>
#include <OpenGL/Renderer/RenderPass/DebugLightCullingPass.hpp>
#include <Core/Window/Window.hpp>

using namespace ax;

RendererViewportHandle RendererGL::createViewport(const Vector2f& position, const Vector2f& size, RenderMode mode)
{
    Id id = m_content.viewports.add(std::make_unique<RendererViewportGL>());
    RendererViewportGL* viewport = m_content.viewports.get(id).get();
    viewport->id = id;
    viewport->content = &m_content;

    viewport->position = position;
    viewport->size = size;
    viewport->resolution = Engine::window().getSize();

    m_content.cullLightSSBO->setResolution(viewport->resolution);
    viewport->setRendermode(mode);

    return viewport;
}
void RendererGL::destroyViewport(RendererViewportHandle& viewportPointer)
{
    RendererViewportGL* viewport = static_cast<RendererViewportGL*>(viewportPointer);
    viewport->renderPass->terminate();
    m_content.viewports.remove(viewport->id);
    viewportPointer = nullptr;
}

void RendererViewportGL::setRendermode(RenderMode mode)
{
    if(renderPass) renderPass->terminate();
    renderPass.reset();

    switch(mode)
    {
        case RenderMode::Default:
            renderPass = std::make_unique<ForwardPlusPass>(*content, *this);
        break;
        case RenderMode::ForwardPlusShading:
            renderPass = std::make_unique<ForwardPlusPass>(*content, *this);
        break;
        case RenderMode::Wireframe:
            renderPass = std::make_unique<WireframePass>(*content, *this);
        break;
        case RenderMode::Debug0:
            renderPass = std::make_unique<DebugLightCullingPass>(*content, *this);
        break;
        default:
            renderPass = std::make_unique<ForwardPlusPass>(*content, *this);
        break;
    }
    
    renderPass->initialize();
}
void RendererViewportGL::setCamera(RendererCameraHandle cameraPointer)
{
    camera = static_cast<RendererCameraGL*>(cameraPointer);
}
void RendererViewportGL::setResolution(const Vector2u& newResolution)
{
    resolution = newResolution;
    content->cullLightSSBO->setResolution(resolution);
    renderPass->updateResolution();
}
void RendererViewportGL::setRectangle(const Vector2f& newPosition, const Vector2f& newSize)
{
    position = newPosition;
    size = newSize;
}