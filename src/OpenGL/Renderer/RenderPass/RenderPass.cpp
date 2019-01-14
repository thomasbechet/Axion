#include <OpenGL/Renderer/RenderPass/RenderPass.hpp>

using namespace ax;

RenderPass::RenderPass(RenderContent& _content, Viewport& _viewport) : 
    content(_content),
    viewport(_viewport)
{
    
}