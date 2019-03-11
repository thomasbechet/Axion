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

    material.parameters = settings;

    m_content.materialUBO->updateMaterial(material);
}
