#include <Core/Prefab/Component/ModelComponent.hpp>

#include <Core/Asset/AssetModule.hpp>
#include <Core/Renderer/RendererModule.hpp>

using namespace ax;

const std::string ModelComponent::type = "Model";

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
        std::get<AssetReference<Mesh>>(reference).reset();
        std::get<AssetReference<Material>>(reference).reset();
    }

    m_elements.clear();
}
void ModelComponent::setModel(std::string name) noexcept
{
    setModel(Engine::asset().model(name));
}
void ModelComponent::setModel(AssetReference<Model> model) noexcept
{
    setModel(nullptr);

    const std::vector<AssetReference<Mesh>>& meshes = model->getMeshes();
    const std::vector<AssetReference<Material>>& materials = model->getMaterials();

    m_elements.reserve(meshes.size());

    for(size_t it = 0; it < meshes.size(); it++)
    {
        RendererStaticmeshHandle staticmesh = Engine::renderer().createStaticmesh();
        staticmesh->setTransform(&transform);
        staticmesh->setMesh(meshes[it]->getHandle());
        staticmesh->setMaterial(materials[it]->getHandle());

        m_elements.emplace_back(std::tuple<AssetReference<Mesh>, AssetReference<Material>, RendererStaticmeshHandle>(
            meshes[it], materials[it], staticmesh
        ));
    }
}
void ModelComponent::setModel(AssetReference<Mesh> mesh) noexcept
{   
    setModel(nullptr);

    AssetReference<Material> material = Engine::asset().material(Material::Default);

    RendererStaticmeshHandle staticmesh = Engine::renderer().createStaticmesh();
    staticmesh->setTransform(&transform);
    staticmesh->setMesh(mesh->getHandle());
    staticmesh->setMaterial(material->getHandle());

    m_elements.emplace_back(std::tuple<AssetReference<Mesh>, AssetReference<Material>, RendererStaticmeshHandle>(
        mesh, material, staticmesh
    ));
}

void ModelComponent::setMaterial(std::nullptr_t ptr, Id component) noexcept
{
    std::tuple<AssetReference<Mesh>, AssetReference<Material>, RendererStaticmeshHandle>& reference = m_elements.at(component);

    std::get<AssetReference<Material>>(reference).reset();

    std::get<RendererStaticmeshHandle>(reference)->setMaterial(nullptr);
}
void ModelComponent::setMaterial(std::string name, Id component) noexcept
{
    setMaterial(Engine::asset().material(name), component);
}
void ModelComponent::setMaterial(AssetReference<Material> material, Id component) noexcept
{
    if(material)
    {
        std::tuple<AssetReference<Mesh>, AssetReference<Material>, RendererStaticmeshHandle>& reference = m_elements.at(component);

        std::get<AssetReference<Material>>(reference).reset();
        std::get<AssetReference<Material>>(reference) = material;

        std::get<RendererStaticmeshHandle>(reference)->setMaterial(std::get<AssetReference<Material>>(reference)->getHandle());
    }
    else
    {
        setMaterial(nullptr, component);
    }   
}