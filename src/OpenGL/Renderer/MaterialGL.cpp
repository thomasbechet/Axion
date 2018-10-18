#include <OpenGL/Renderer/RendererGL.hpp>

using namespace ax;

//Material
Id RendererGL::createMaterial(RendererMaterialParameters settings)
{
    Id id = m_materials.add(std::pair<MaterialGL, std::vector<Id>>());
    MaterialGL& material = m_materials.get(id).first;

    material.useDiffuseTexture = settings.useDiffuseTexture;
    material.diffuseColor = settings.diffuseColor;
    material.diffuseTexture = settings.diffuseTexture;

    return id;
}
void RendererGL::destroyMaterial(Id id)
{
    m_materials.remove(id);
}