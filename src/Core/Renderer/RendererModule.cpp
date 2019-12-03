#include <Core/Renderer/RendererModule.hpp>

using namespace ax;
using namespace ax::detail;

void RendererModule::setDefaultViewport(RendererGUIViewportHandle viewport) noexcept
{
    m_defaultViewport = viewport;
}
RendererGUIViewportHandle RendererModule::getDefaultViewport() const noexcept
{
    return m_defaultViewport;
}