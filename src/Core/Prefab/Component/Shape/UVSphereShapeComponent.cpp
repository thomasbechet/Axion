#include <Core/Prefab/Component/Shape/UVSphereShapeComponent.hpp>

#include <Core/Asset/AssetModule.ipp>
#include <Core/Renderer/RendererModule.hpp>
#include <Core/Math/Geometry/UVSphere.hpp>

using namespace ax;

UVSphereShapeComponent::UVSphereShapeComponent(const Entity& entity, const Json& json) :
    transform(entity.getComponent<TransformComponent>())
{

}
UVSphereShapeComponent::UVSphereShapeComponent(const Entity& entity,
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
    m_staticmesh->setTransform(&transform);
    m_staticmesh->setMesh(m_mesh);
    m_material = Engine::asset().get<Material>(Material::Default);
    m_staticmesh->setMaterial(m_material->getHandle());
}
UVSphereShapeComponent::~UVSphereShapeComponent()
{
    Engine::renderer().destroyStaticmesh(m_staticmesh);
    Engine::renderer().destroyMesh(m_mesh);
}

void UVSphereShapeComponent::setMaterial(std::nullptr_t ptr) noexcept
{
    m_material.reset();
    m_staticmesh->setMaterial(nullptr);
}
void UVSphereShapeComponent::setMaterial(const std::string& name) noexcept
{
    setMaterial(Engine::asset().get<Material>(name));
}
void UVSphereShapeComponent::setMaterial(Reference<Material> material) noexcept
{
    if(material)
    {
        m_material.reset();
        m_material = material;

        m_staticmesh->setMaterial(m_material->getHandle());
    }
    else
    {
        setMaterial(nullptr);
    }   
}

void UVSphereShapeComponent::setSmooth(bool smooth) noexcept
{
    m_smooth = smooth;
}
void UVSphereShapeComponent::setCoordinateFactor(float factor) noexcept
{
    m_coordinateFactor = factor;
}

void UVSphereShapeComponent::generate() noexcept
{
    m_mesh->update(UVSphere::vertices(m_radius, m_UN, m_VN, m_smooth, m_coordinateFactor));
}