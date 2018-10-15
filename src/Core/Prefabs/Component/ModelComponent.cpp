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
    m_model.reset();
}
void ModelComponent::setModel(std::string name) noexcept
{

}
void ModelComponent::setModel(AssetReference<Model> model) noexcept
{

}

void ModelComponent::loadModelChilds() noexcept
{
    size_t size = m_model->meshes.size();
    for(size_t it = 0; it < size; it++)
    {
        Entity* entity = &Engine::world().entities().create();
        entity->addComponent<TransformComponent>().attachTo(transform);
        MeshComponent& mesh = entity->addComponent<MeshComponent>(*entity);
    }
}
void ModelComponent::unloadModelChilds() noexcept
{

}