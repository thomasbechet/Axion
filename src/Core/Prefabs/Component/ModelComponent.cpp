#include <Core/Prefabs/Component/ModelComponent.hpp>

using namespace ax;

ModelComponent::ModelComponent(const Entity& entity) :
    transform(entity.getComponent<TransformComponent>())
{

}
ModelComponent::~ModelComponent()
{

}

void ModelComponent::setModel(std::nullptr_t) noexcept
{
    for(auto& reference : m_components)
    {
        Engine::renderer().destroyStaticmesh(std::get<Id>(reference));
        std::get<Mesh>(reference).reset();
        std::get<Material>(reference).reset();
    }

    m_components.clear();
}
void ModelComponent::setModel(std::string name) noexcept
{
    setModel(Engine::assets().model(name));
}
void ModelComponent::setModel(AssetReference<Model> model) noexcept
{
    setModel(nullptr);


}
void ModelComponent::setModel(AssetReference<Mesh> mesh) noexcept
{   
    setModel(nullptr);

    Id id = Engine::renderer().createStaticmesh();
    Engine::renderer().setStaticmeshTransform(id, transform);
    Engine::renderer().setStaticmeshMesh(id, mesh->handle);
}

void ModelComponent::setMaterial(std::nullptr_t, Id component = 0) noexcept
{
    std::tuple<Mesh, Material, Id>& reference = m_components.at(component);

    std::get<Material>(reference).reset();

    Engine::renderer().setStaticmeshMaterial(std::get<Id>(reference), 0);
}
void ModelComponent::setMaterial(std::string name, Id component = 0) noexcept
{
    setMaterial(Engine::assets().material(name), component);
}
void ModelComponent::setMaterial(AssetReference<Material> material, Id component = 0) noexcept
{
    if(material)
    {
        std::tuple<Mesh, Material, Id>& reference = m_components.at(component);

        std::get<Material>(reference).reset();
        std::get<Material>(reference) = material;

        Engine::renderer().setStaticmeshMaterial(std::get<Id>(reference), std::get<Material>(reference)->handle);
    }
    else
    {
        setMaterial(nullptr, component);
    }   
}