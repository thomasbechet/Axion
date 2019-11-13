#include <Core/Content/Component/ModelComponent.hpp>

#include <Core/Asset/AssetModule.ipp>
#include <Core/Renderer/RendererModule.hpp>

using namespace ax;

ModelComponent::ModelComponent(const Entity& entity, const Json& json) :
    transform(entity.getComponent<TransformComponent>())
{
    try
    {
        if(json.is_string())
            setModel(json.get<std::string>());
    }
    catch(...) {}
}
ModelComponent::ModelComponent(const Entity& entity) :
    transform(entity.getComponent<TransformComponent>())
{

}
ModelComponent::~ModelComponent()
{
    setModel(nullptr);
}

void ModelComponent::setModel(std::nullptr_t) noexcept
{
    for(auto& reference : m_elements)
    {
        Engine::renderer().destroyStaticmesh(std::get<RendererStaticmeshHandle>(reference));
        std::get<Reference<Mesh>>(reference).reset();
        std::get<Reference<Material>>(reference).reset();
    }

    m_elements.clear();
}
void ModelComponent::setModel(const std::string& name) noexcept
{
    setModel(Engine::asset().get<Model>(name));
}
void ModelComponent::setModel(Reference<Model> model) noexcept
{
    setModel(nullptr);

    const std::vector<Reference<Mesh>>& meshes = model->getMeshes();
    const std::vector<Reference<Material>>& materials = model->getMaterials();

    m_elements.reserve(meshes.size());

    for(size_t it = 0; it < meshes.size(); it++)
    {
        RendererStaticmeshHandle staticmesh = Engine::renderer().createStaticmesh();
        staticmesh->setTransform(&transform);
        staticmesh->setMesh(meshes[it]->getHandle());
        staticmesh->setMaterial(materials[it]->getHandle());

        m_elements.emplace_back(std::tuple<Reference<Mesh>, Reference<Material>, RendererStaticmeshHandle>(
            meshes[it], materials[it], staticmesh
        ));
    }
}
void ModelComponent::setModel(Reference<Mesh> mesh) noexcept
{   
    setModel(nullptr);

    Reference<Material> material = Engine::asset().get<Material>(Material::Default);

    RendererStaticmeshHandle staticmesh = Engine::renderer().createStaticmesh();
    staticmesh->setTransform(&transform);
    staticmesh->setMesh(mesh->getHandle());
    staticmesh->setMaterial(material->getHandle());

    m_elements.emplace_back(std::tuple<Reference<Mesh>, Reference<Material>, RendererStaticmeshHandle>(
        mesh, material, staticmesh
    ));
}

void ModelComponent::setMaterial(std::nullptr_t ptr, Id component) noexcept
{
    std::tuple<Reference<Mesh>, Reference<Material>, RendererStaticmeshHandle>& reference = m_elements.at(component);

    std::get<Reference<Material>>(reference).reset();

    std::get<RendererStaticmeshHandle>(reference)->setMaterial(nullptr);
}
void ModelComponent::setMaterial(const std::string& name, Id component) noexcept
{
    setMaterial(Engine::asset().get<Material>(name), component);
}
void ModelComponent::setMaterial(Reference<Material> material, Id component) noexcept
{
    if(material)
    {
        std::tuple<Reference<Mesh>, Reference<Material>, RendererStaticmeshHandle>& reference = m_elements.at(component);

        std::get<Reference<Material>>(reference).reset();
        std::get<Reference<Material>>(reference) = material;

        std::get<RendererStaticmeshHandle>(reference)->setMaterial(std::get<Reference<Material>>(reference)->getHandle());
    }
    else
    {
        setMaterial(nullptr, component);
    }   
}