#include <OpenGL/Renderer/StaticmeshGL.hpp>

using namespace ax;

//Staticmesh
Id RendererGL::createStaticmesh()
{
    Id id = m_staticmeshes.add(StaticmeshGL());

    return id;
}
void RendererGL::destroyStaticmesh(Id id)
{
    //Unbind material pool

    m_staticmeshes.remove(id);
}
void RendererGL::setStaticmeshMaterial(Id id, Id material)
{

}
void RendererGL::setStaticmeshTransform(Id id, Transform* transform)
{
    m_staticmeshes.get(id).transform = transform;
}
void RendererGL::setStaticmeshMesh(Id id, Id mesh)
{
    m_staticmeshes.get(id).mesh = mesh;
}
