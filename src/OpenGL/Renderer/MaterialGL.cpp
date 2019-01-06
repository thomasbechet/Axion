#include <OpenGL/Renderer/RendererGL.hpp>

using namespace ax;

//Material
Id RendererGL::createMaterial(const RendererMaterialParameters& params)
{
    Id id = m_content.materials.add(std::pair<MaterialGL, std::vector<Id>>());
    MaterialGL& material = m_content.materials.get(id).first;    

    m_content.materialUBO->load(material);
    updateMaterial(id, params);

    return id;
}
void RendererGL::destroyMaterial(Id id)
{
    MaterialGL& material = m_content.materials.get(id).first;

    m_content.materialUBO->unload(material);

    m_content.materials.remove(id);
}
void RendererGL::updateMaterial(Id id, const RendererMaterialParameters& settings)
{
    MaterialGL& material = m_content.materials.get(id).first;

    material.useDiffuseTexture = settings.useDiffuseTexture;
    material.useDiffuseColor = settings.useDiffuseColor;
    material.diffuseColor = settings.diffuseColor;
    material.diffuseTexture = settings.diffuseTexture;

    material.useNormalTexture = settings.useNormalTexture;
    material.isBumpTexture = settings.isBumpTexture;
    material.normalTexture = settings.normalTexture;

    material.useSpecularTexture = settings.useSpecularTexture;
    material.specularUniform = settings.specularUniform;
    material.specularTexture = settings.specularTexture;

    m_content.materialUBO->update(material);
}
