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
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

//Mesh
Id RendererGL::loadMesh(const Mesh& mesh) noexcept
{
    MeshGL mesh;
    

    return 0;
}
void RendererGL::unloadMesh(Id mesh) noexcept
{

}   
//Material
Id RendererGL::loadMaterial(const Material& material) noexcept
{
    return 0;
}
void RendererGL::unloadMaterial(Id material) noexcept
{

}
//Texture
Id RendererGL::loadTexture(const Texture& texture) noexcept
{
    return 0;
}
void RendererGL::unloadTexture(Id material) noexcept
{

}

//Camera
Id RendererGL::createCamera() noexcept
{

}
void RendererGL::destroyCamera(Id id) noexcept
{

}
void RendererGL::setCameraTransform(Id id, const Transform& transform) noexcept
{

}
void RendererGL::setCameraSettings(Id id, CameraSettings settings) noexcept
{

}

//Staticmesh
Id RendererGL::createStaticmesh() noexcept
{
    return 0;
}
void RendererGL::destroyStaticmesh(Id id) noexcept
{
    
}
void RendererGL::setStaticmeshMaterial(Id id, std::string name) noexcept
{
    
}
void RendererGL::setStaticmeshTransform(Id id, const Transform& trans) noexcept
{
    
}
void RendererGL::setStaticmeshMesh(Id id, std::string name) noexcept
{
    
}
    
void RendererGL::updateViewport() noexcept
{
    
}