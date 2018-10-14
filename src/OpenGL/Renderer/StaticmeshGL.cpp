#include <OpenGL/Renderer/RendererGL.hpp>

#include <algorithm>

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
    StaticmeshGL& staticmesh = m_staticmeshes.get(id);
    if(staticmesh.material)
    {
        std::vector<Id>& meshes = m_materials.at(staticmesh.material).second;
        meshes.erase(std::remove(meshes.begin(), meshes.end(), id), meshes.end());
    }

    staticmesh.material = material;
    if(staticmesh.material)
    {
        std::vector<Id>& meshes = m_materials.at(staticmesh.material).second;
        meshes.push_back(id);
    }
}
void RendererGL::setStaticmeshTransform(Id id, Transform* transform)
{
    m_staticmeshes.get(id).transform = transform;
}
void RendererGL::setStaticmeshMesh(Id id, Id mesh)
{
    m_staticmeshes.get(id).mesh = mesh;
}
