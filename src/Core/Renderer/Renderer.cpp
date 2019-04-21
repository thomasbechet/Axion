#include <Core/Renderer/Renderer.hpp>

using namespace ax;

void Renderer::setDefaultViewport(RendererGUIViewportHandle viewport) noexcept
{
    m_defaultViewport = viewport;
}
RendererGUIViewportHandle Renderer::getDefaultViewport() const noexcept
{
    return m_defaultViewport;
}