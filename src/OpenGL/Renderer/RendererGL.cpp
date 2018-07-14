#include <OpenGL/Renderer/RendererGL.hpp>

#include <Core/Context/Game.hpp>
#include <GL/glew.h>

using namespace ax;

void RendererGL::initialize() noexcept
{
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
        Game::interrupt("Failed to initialize GLEW");
}
void RendererGL::terminate() noexcept
{

}
void RendererGL::update(double alpha) noexcept
{
    glViewport(50, 50, 100, 100);
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

Renderer::Id RendererGL::createStaticmesh() noexcept
{
    return 0;
}
void RendererGL::destroyStaticmesh(Renderer::Id id) noexcept
{
    
}
void RendererGL::setStaticmeshMaterial(Renderer::Id id, std::string name) noexcept
{
    
}
void RendererGL::setStaticmeshTransform(Renderer::Id id, const Transform& trans) noexcept
{
    
}
void RendererGL::setStaticmeshMesh(Renderer::Id id, std::string name) noexcept
{
    
}
    
void RendererGL::updateViewport() noexcept
{
    
}