#include <Core/Renderer/Renderer.hpp>

using namespace ax;

void Renderer::setDefaultViewport(RendererViewportHandle viewport) noexcept
{
    m_defaultViewport = viewport;
}
RendererViewportHandle Renderer::getDefaultViewport() const noexcept
{
    return m_defaultViewport;
}