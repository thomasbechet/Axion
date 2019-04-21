#include <OpenGL/Renderer/GUI/RendererGUIViewportGL.hpp>
#include <OpenGL/Renderer/RendererGL.hpp>

#include <OpenGL/Renderer/RenderPass/ForwardPlusPass.hpp>
#include <OpenGL/Renderer/RenderPass/WireframePass.hpp>
#include <OpenGL/Renderer/RenderPass/DebugLightCullingPass.hpp>
#include <Core/Window/Window.hpp>

using namespace ax;

RendererGUIViewportHandle RendererGL::createViewport(const Vector2f& position, const Vector2f& size, RenderMode mode)
{
    Id id = m_content.viewports.add(std::make_unique<RendererGUIViewportGL>());
    RendererGUIViewportGL* viewport = m_content.viewports.get(id).get();
    viewport->id = id;
    viewport->content = &m_content;

    viewport->position = position;
    viewport->size = size;
    viewport->resolution = Engine::window().getSize();

    m_content.cullLightSSBO->setResolution(viewport->resolution);
    viewport->setRendermode(mode);

    return viewport;
}
void RendererGL::destroyViewport(RendererGUIViewportHandle& viewportPointer)
{
    RendererGUIViewportGL* viewport = static_cast<RendererGUIViewportGL*>(viewportPointer);
    viewport->renderPass->terminate();
    m_content.viewports.remove(viewport->id);
    viewportPointer = nullptr;
}

void RendererGUIViewportGL::setRendermode(RenderMode mode)
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
void RendererGUIViewportGL::setCamera(RendererCameraHandle cameraPointer)
{
    camera = static_cast<RendererCameraGL*>(cameraPointer);
}
void RendererGUIViewportGL::setResolution(const Vector2u& newResolution)
{
    resolution = newResolution;
    content->cullLightSSBO->setResolution(resolution);
    renderPass->updateResolution();
}
void RendererGUIViewportGL::setRectangle(const Vector2f& newPosition, const Vector2f& newSize)
{
    position = newPosition;
    size = newSize;
}