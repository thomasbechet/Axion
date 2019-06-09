#include <OpenGL/Renderer/GUI/RendererGUIViewportGL.hpp>
#include <OpenGL/Renderer/RendererGL.hpp>

#include <OpenGL/Renderer/Shader/ShaderConstants.hpp>
#include <OpenGL/Renderer/RenderPass/ForwardPlusPass.hpp>
#include <OpenGL/Renderer/RenderPass/WireframePass.hpp>
#include <Core/Window/Window.hpp>

using namespace ax;

RendererGUIViewportHandle RendererGL::createViewport(const Rectf& rect, const Vector2u& resolution, RenderMode mode)
{
    Id id = m_content.viewports.add(std::make_unique<RendererGUIViewportGL>(m_content, rect, resolution, mode));
    RendererGUIViewportGL* viewport = m_content.viewports.get(id).get();
    viewport->setID(id);

    if(USE_LIGHT_CULLING) m_content.cullLightSSBO->setResolution(resolution);

    return viewport;
}
void RendererGL::destroyViewport(RendererGUIViewportHandle& viewportPointer)
{
    RendererGUIViewportGL* viewport = static_cast<RendererGUIViewportGL*>(viewportPointer);
    m_content.viewports.remove(viewport->getID());
    viewportPointer = nullptr;
}

RendererGUIViewportGL::RendererGUIViewportGL(RenderContent& content, const Rectf& rect, const Vector2u& resolution, RenderMode mode) : 
    m_content(content),
    m_renderBuffer(std::make_unique<RenderBuffer>(resolution)),
    m_viewport(rect),
    m_resolution(resolution)
{
    setRendermode(mode);
}   
RendererGUIViewportGL::~RendererGUIViewportGL()
{
    m_renderPass->onTerminate();
}

void RendererGUIViewportGL::setRendermode(RenderMode mode)
{
    if(m_renderPass) m_renderPass->onTerminate();
    m_renderPass.reset();

    switch(mode)
    {
        case RenderMode::Default: m_renderPass = std::make_unique<ForwardPlusPass>(m_content, *this, false); break;
        case RenderMode::ForwardPlusShading: m_renderPass = std::make_unique<ForwardPlusPass>(m_content, *this, false); break;
        case RenderMode::Wireframe: m_renderPass = std::make_unique<WireframePass>(m_content, *this); break;
        case RenderMode::Debug0: m_renderPass = std::make_unique<ForwardPlusPass>(m_content, *this, true); break;
        default: m_renderPass = std::make_unique<ForwardPlusPass>(m_content, *this, false); break;
    }
    
    m_renderPass->onInitialize(m_resolution);
}
void RendererGUIViewportGL::setCamera(RendererCameraHandle cameraPointer)
{
    m_camera = static_cast<RendererCameraGL*>(cameraPointer);
}
void RendererGUIViewportGL::setResolution(const Vector2u& newResolution)
{
    m_resolution = newResolution;
    m_renderBuffer.reset(new RenderBuffer(m_resolution));
    m_content.cullLightSSBO->setResolution(m_resolution);
    m_renderPass->onUpdateResolution(m_resolution);
}
void RendererGUIViewportGL::setViewport(const Rectf& rect)
{
    m_viewport = rect;
}

void RendererGUIViewportGL::render(double alpha) const noexcept
{
    m_renderBuffer->clear(m_clearColor);

    if(m_camera)
    {
        m_renderPass->onRender(*m_renderBuffer.get(), *m_camera, alpha);
    }
}

RenderBuffer& RendererGUIViewportGL::getRenderBuffer() const noexcept
{
    return *m_renderBuffer.get();
}
Rectu RendererGUIViewportGL::getViewport() const noexcept
{
    Rectu rect;
    Vector2u windowSize = Engine::window().getSize();
    rect.left = (unsigned)(m_viewport.left * (float)windowSize.x);
    rect.bottom = (unsigned)(m_viewport.bottom * (float)windowSize.y);
    rect.width = (unsigned)(m_viewport.width * (float)windowSize.x);
    rect.height = (unsigned)(m_viewport.height * (float)windowSize.y);
    return rect;
}

void RendererGUIViewportGL::setID(Id id) noexcept
{
    m_id = id;
}
Id RendererGUIViewportGL::getID() const noexcept
{
    return m_id;
}