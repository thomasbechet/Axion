#include <Core/Prefabs/Component/MeshComponent.hpp>

#include <Core/Renderer/Renderer.hpp>
#include <Core/Assets/AssetManager.hpp>

using namespace ax;

MeshComponent::MeshComponent(const Entity& entity) :
    transform(entity.getComponent<TransformComponent>())
{
    m_handle = Engine::renderer().createStaticmesh();
    Engine::renderer().setStaticmeshTransform(m_handle, &transform);
    Engine::renderer().setStaticmeshMesh(m_handle, 0);
    Engine::renderer().setStaticmeshMaterial(m_handle, 0);
}
MeshComponent::~MeshComponent()
{
    Engine::renderer().destroyStaticmesh(m_handle);
}
#include <iostream>
void MeshComponent::setMesh(std::string& name) noexcept
{
    std::cout << "YERA merde" << std::endl;

    m_mesh = Engine::assets().mesh(name);
    Engine::renderer().setStaticmeshMesh(m_handle, m_mesh->handle);
}
void MeshComponent::setMesh(AssetReference<Mesh> mesh) noexcept
{
    std::cout << "YERA" << std::endl;

    m_mesh = mesh;
    if(m_mesh)
        Engine::renderer().setStaticmeshMesh(m_handle, m_mesh->handle);
    else
        Engine::renderer().setStaticmeshMesh(m_handle, 0);
}
void MeshComponent::setMaterial(std::string name) noexcept
{
    m_material = Engine::assets().material(name);
    Engine::renderer().setStaticmeshMaterial(m_handle, m_material->handle);
}
void MeshComponent::setMaterial(AssetReference<Material> material) noexcept
{
    m_material = material;
    if(m_material)
        Engine::renderer().setStaticmeshMaterial(m_handle, m_material->handle);
    else
        Engine::renderer().setStaticmeshMaterial(m_handle, 0);
}