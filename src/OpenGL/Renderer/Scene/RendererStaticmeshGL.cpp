#include <OpenGL/Renderer/Scene/RendererStaticmeshGL.hpp>
#include <OpenGL/Renderer/RendererGL.hpp>

#include <algorithm>

using namespace ax;

RendererStaticmeshHandle RendererGL::createStaticmesh()
{
    Id id = m_content.staticmeshes.add(std::make_unique<RendererStaticmeshGL>());
    RendererStaticmeshGL* staticmesh = m_content.staticmeshes.get(id).get();
    staticmesh->id = id;
    staticmesh->content = &m_content;
    
    return staticmesh;
}
void RendererGL::destroyStaticmesh(RendererStaticmeshHandle& staticmeshPointer)
{
    RendererStaticmeshGL* staticmesh = static_cast<RendererStaticmeshGL*>(staticmeshPointer);
    staticmesh->setMaterial(nullptr);
    Id id = staticmesh->id;
    m_content.staticmeshes.remove(id);
    staticmeshPointer = nullptr;
}

void RendererStaticmeshGL::setTransform(Transform* transformPointer)
{
    transform = transformPointer;
}
void RendererStaticmeshGL::setMaterial(RendererMaterialHandle materialPointer)
{   
    if(material)
    {
        std::vector<RendererStaticmeshGL*>& meshes = content->materials.get(material->id).second;
        meshes.erase(std::remove(meshes.begin(), meshes.end(), this), meshes.end());
    }

    material = static_cast<RendererMaterialGL*>(materialPointer);
    if(material)
    {
        std::vector<RendererStaticmeshGL*>& meshes = content->materials.get(material->id).second;
        meshes.push_back(this);
    }
}
void RendererStaticmeshGL::setMesh(RendererMeshHandle meshPointer)
{
    mesh = static_cast<RendererMeshGL*>(meshPointer);
}