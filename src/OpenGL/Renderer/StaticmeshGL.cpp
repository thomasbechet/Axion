#include <OpenGL/Renderer/RendererGL.hpp>

#include <algorithm>

using namespace ax;

//Staticmesh
Id RendererGL::createStaticmesh()
{
    Id id = m_content.staticmeshes.add(StaticmeshGL());

    return id;
}
void RendererGL::destroyStaticmesh(Id id)
{
    //Unbind material pool

    m_content.staticmeshes.remove(id);
}
void RendererGL::setStaticmeshMaterial(Id id, Id material)
{
    StaticmeshGL& staticmesh = m_content.staticmeshes.get(id);
    if(staticmesh.material)
    {
        std::vector<Id>& meshes = m_content.materials.get(staticmesh.material).second;
        meshes.erase(std::remove(meshes.begin(), meshes.end(), id), meshes.end());
    }

    staticmesh.material = material;
    if(staticmesh.material)
    {
        std::vector<Id>& meshes = m_content.materials.get(staticmesh.material).second;
        meshes.push_back(id);
    }
}
void RendererGL::setStaticmeshTransform(Id id, Transform* transform)
{
    m_content.staticmeshes.get(id).transform = transform;
}
void RendererGL::setStaticmeshMesh(Id id, Id mesh)
{
    m_content.staticmeshes.get(id).mesh = mesh;
}
