#include <OpenGL/Renderer/RendererModuleGL.hpp>

using namespace ax;

extern "C"
{
    RendererModule* create_renderer()
    {
        return new RendererModuleGL();
    }
}