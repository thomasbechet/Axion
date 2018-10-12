#include <Core/Prefabs/Component/StaticMeshComponent.hpp>

#include <Core/Renderer/Renderer.hpp>
#include <Core/Assets/AssetManager.hpp>

using namespace ax;

StaticMeshComponent::StaticMeshComponent(const Entity& entity) :
    transform(entity.getComponent<TransformComponent>())
{
    m_handle = Engine::renderer().createStaticmesh();
    Engine::renderer().setStaticmeshTransform(m_handle, &transform);
    Engine::renderer().setStaticmeshMesh(m_handle, 0);
}
StaticMeshComponent::~StaticMeshComponent()
{
    Engine::renderer().destroyStaticmesh(m_handle);
}

void StaticMeshComponent::setMesh(std::string name) noexcept
{
    m_mesh = Engine::assets().mesh(name);
    Engine::renderer().setStaticmeshMesh(m_handle, m_mesh->handle);
}
void StaticMeshComponent::setMesh(AssetReference<Mesh>& mesh) noexcept
{
    m_mesh = mesh;
    Engine::renderer().setStaticmeshMesh(m_handle, m_mesh->handle);
}