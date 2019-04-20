#include <OpenGL/Renderer/Asset/RendererMaterialGL.hpp>
#include <OpenGL/Renderer/RendererGL.hpp>

using namespace ax;

RendererMaterialHandle RendererGL::createMaterial(const RendererMaterialParameters& settings)
{
    Id id = m_content.materials.add(std::make_pair(
        std::make_unique<RendererMaterialGL>(), std::vector<RendererStaticmeshGL*>()
    ));
    RendererMaterialGL* material = m_content.materials.get(id).first.get();
    material->id = id;
    material->content = &m_content;

    m_content.materialUBO->load(*material);
    material->update(settings);

    return material;
}
void RendererGL::destroyMaterial(RendererMaterialHandle& materialPointer)
{
    RendererMaterialGL* material = static_cast<RendererMaterialGL*>(materialPointer);
    m_content.materialUBO->unload(*material);
    m_content.materials.remove(material->id);
    materialPointer = nullptr;
}

void RendererMaterialGL::update(const RendererMaterialParameters& settings)
{
    parameters = settings;
    content->materialUBO->updateMaterial(*this);
}