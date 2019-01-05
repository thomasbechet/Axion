#include <Core/Prefab/Component/ModelComponent.hpp>

#include <Core/Renderer/Renderer.hpp>
#include <Core/Asset/AssetManager.hpp>

using namespace ax;

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
        Engine::renderer().destroyStaticmesh(std::get<Id>(reference));
        std::get<AssetReference<Mesh>>(reference).reset();
        std::get<AssetReference<Material>>(reference).reset();
    }

    m_elements.clear();
}
void ModelComponent::setModel(std::string name) noexcept
{
    setModel(Engine::assets().model(name));
}
void ModelComponent::setModel(AssetReference<Model> model) noexcept
{
    setModel(nullptr);

    const std::vector<AssetReference<Mesh>>& meshes = model->getMeshes();
    const std::vector<AssetReference<Material>>& materials = model->getMaterials();

    m_elements.reserve(meshes.size());

    for(size_t it = 0; it < meshes.size(); it++)
    {
        Id id = Engine::renderer().createStaticmesh();
        Engine::renderer().setStaticmeshTransform(id, &transform);
        Engine::renderer().setStaticmeshMesh(id, meshes[it]->getHandle());
        Engine::renderer().setStaticmeshMaterial(id, materials[it]->getHandle());

        m_elements.emplace_back(std::tuple<AssetReference<Mesh>, AssetReference<Material>, Id>(
            meshes[it], materials[it], id
        ));
    }
}
void ModelComponent::setModel(AssetReference<Mesh> mesh) noexcept
{   
    setModel(nullptr);

    AssetReference<Material> material = Engine::assets().material(Material::Default);

    Id id = Engine::renderer().createStaticmesh();
    Engine::renderer().setStaticmeshTransform(id, &transform);
    Engine::renderer().setStaticmeshMesh(id, mesh->getHandle());
    Engine::renderer().setStaticmeshMaterial(id, material->getHandle());

    m_elements.emplace_back(std::tuple<AssetReference<Mesh>, AssetReference<Material>, Id>(
        mesh, material, id
    ));
}

void ModelComponent::setMaterial(std::nullptr_t ptr, Id component) noexcept
{
    std::tuple<AssetReference<Mesh>, AssetReference<Material>, Id>& reference = m_elements.at(component);

    std::get<AssetReference<Material>>(reference).reset();

    Engine::renderer().setStaticmeshMaterial(std::get<Id>(reference), 0);
}
void ModelComponent::setMaterial(std::string name, Id component) noexcept
{
    setMaterial(Engine::assets().material(name), component);
}
void ModelComponent::setMaterial(AssetReference<Material> material, Id component) noexcept
{
    if(material)
    {
        std::tuple<AssetReference<Mesh>, AssetReference<Material>, Id>& reference = m_elements.at(component);

        std::get<AssetReference<Material>>(reference).reset();
        std::get<AssetReference<Material>>(reference) = material;

        Engine::renderer().setStaticmeshMaterial(std::get<Id>(reference), std::get<AssetReference<Material>>(reference)->getHandle());
    }
    else
    {
        setMaterial(nullptr, component);
    }   
}