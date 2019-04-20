#include <OpenGL/Renderer/RenderPass/RenderPass.hpp>

using namespace ax;

RenderPass::RenderPass(RenderContent& _content, RendererViewportGL& _viewport) : 
    content(_content),
    viewport(_viewport)
{
    
}