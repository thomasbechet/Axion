#include <Core/Prefab/Component/Shape/UVSphereComponent.hpp>

#include <Core/Renderer/Renderer.hpp>
#include <Core/Math/Geometry/UVSphere.hpp>
#include <Core/Asset/AssetManager.hpp>

using namespace ax;

const std::string UVSphereComponent::name = "UVSphere";

UVSphereComponent::UVSphereComponent(const Entity& entity,
        float radius,
        unsigned slice,
        unsigned stack,
        bool smooth,
        float factor
    ) :
    UVSphere(radius, slice, stack),
    transform(entity.getComponent<TransformComponent>()),
    m_smooth(smooth),
    m_coordinateFactor(factor)
{
    //Mesh
    m_mesh = Engine::renderer().createMesh(UVSphere::vertices(m_radius, m_UN, m_VN, m_smooth, m_coordinateFactor));

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

void UVSphereComponent::setMaterial(std::nullptr_t ptr) noexcept
{
    m_material.reset();
    Engine::renderer().setStaticmeshMaterial(m_staticmesh, 0);
}
void UVSphereComponent::setMaterial(std::string name) noexcept
{
    setMaterial(Engine::assets().material(name));
}
void UVSphereComponent::setMaterial(AssetReference<Material> material) noexcept
{
    if(material)
    {
        m_material.reset();
        m_material = material;

        Engine::renderer().setStaticmeshMaterial(m_staticmesh, m_material->getHandle());
    }
    else
    {
        setMaterial(nullptr);
    }   
}

void UVSphereComponent::setSmooth(bool smooth) noexcept
{
    m_smooth = smooth;
}
void UVSphereComponent::setCoordinateFactor(float factor) noexcept
{
    m_coordinateFactor = factor;
}

void UVSphereComponent::generate() noexcept
{
    Engine::renderer().updateMesh(m_mesh, UVSphere::vertices(m_radius, m_UN, m_VN, m_smooth, m_coordinateFactor));
}