#include <OpenGL/Renderer/RendererGL.hpp>

using namespace ax;

extern "C"
{
    Renderer* create_renderer()
    {
        return new RendererGL();
    }
}