#include <OpenGL/Renderer/RendererGL.hpp>

using namespace ax;

//Material
Id RendererGL::createMaterial(RendererMaterialParameters settings)
{
    Id id = m_content.materials.add(std::pair<MaterialGL, std::vector<Id>>());
    MaterialGL& material = m_content.materials.get(id).first;

    material.useDiffuseTexture = settings.useDiffuseTexture;
    material.diffuseColor = settings.diffuseColor;
    material.diffuseTexture = settings.diffuseTexture;

    material.useNormalTexture = settings.useNormalTexture;
    material.isBumpTexture = settings.isBumpTexture;
    material.normalTexture = settings.normalTexture;

    m_content.materialUBO->load(material);

    return id;
}
void RendererGL::destroyMaterial(Id id)
{
    MaterialGL& material = m_content.materials.get(id).first;

    m_content.materialUBO->unload(material);

    m_content.materials.remove(id);
}