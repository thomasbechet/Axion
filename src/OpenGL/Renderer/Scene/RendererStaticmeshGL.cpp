#include <OpenGL/Renderer/Scene/RendererStaticmeshGL.hpp>

#include <OpenGL/Renderer/RendererGL.hpp>

#include <algorithm>

using namespace ax;

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
        std::vector<RendererStaticmeshGL*>& meshes = content.materials.get(staticmesh.material).second;
        meshes.push_back(this);
    }
}
void RendererStaticmeshGL::setMesh(RendererMeshHandle meshPointer)
{
    mesh = static_cast<RendererMeshGL*>(meshPointer);
}