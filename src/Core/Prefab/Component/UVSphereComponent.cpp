#include <Core/Prefab/Component/UVSphereComponent.hpp>

#include <Core/Renderer/Renderer.hpp>
#include <Core/Math/Geometry/UVSphere.hpp>
#include <Core/Asset/AssetManager.hpp>

using namespace ax;

UVSphereComponent::UVSphereComponent(const Entity& entity) :
    transform(entity.getComponent<TransformComponent>())
{
    //Mesh
    m_mesh = Engine::renderer().createMesh(UVSphere::vertices(m_radius, m_UN, m_VN, m_smooth));

    //Staticmesh
    m_staticmesh = Engine::renderer().createStaticmesh();
    Engine::renderer().setStaticmeshTransform(m_staticmesh, &transform);
    Engine::renderer().setStaticmeshMesh(m_staticmesh, m_mesh);
    m_material = Engine::assets().material(Material::Default);
    Engine::renderer().setStaticmeshMaterial(m_staticmesh, m_material->getHandle());
}
UVSphereComponent::~UVSphereComponent()
{
    Engine::renderer().destroyStaticmesh(m_staticmesh);
    Engine::renderer().destroyMesh(m_mesh);
}

void UVSphereComponent::generate() noexcept
{
    Engine::renderer().updateMesh(m_mesh, UVSphere::vertices(m_radius, m_UN, m_VN, m_smooth));
}