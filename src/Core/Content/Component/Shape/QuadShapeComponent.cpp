#include <Core/Content/Component/Shape/QuadShapeComponent.hpp>

#include <Core/Asset/AssetModule.ipp>
#include <Core/Renderer/RendererModule.hpp>

using namespace ax;

QuadShapeComponent::QuadShapeComponent(const Entity& entity, const Json& json) :
    transform(entity.getComponent<TransformComponent>())
{
    
}
QuadShapeComponent::QuadShapeComponent(const Entity& entity, float x, float y, float factor) :
    Quad(x, y),
    transform(entity.getComponent<TransformComponent>()),
    m_coordinateFactor(factor)
{
    //Mesh
    m_mesh = Engine::renderer().createMesh(
        Quad::vertices(
            m_x, m_y,
            m_coordinateFactor
        )
    );

    //Staticmesh
    m_staticmesh = Engine::renderer().createStaticmesh();
    m_staticmesh->setTransform(&transform);
    m_staticmesh->setMesh(m_mesh);
    m_material = Engine::asset().get<Material>(Material::Default);
    m_staticmesh->setMaterial(m_material->getHandle());
}
QuadShapeComponent::~QuadShapeComponent()
{
    Engine::renderer().destroyStaticmesh(m_staticmesh);
    Engine::renderer().destroyMesh(m_mesh);
}

void QuadShapeComponent::setMaterial(std::nullptr_t ptr) noexcept
{
    m_material.reset();
    m_staticmesh->setMaterial(nullptr);
}
void QuadShapeComponent::setMaterial(const std::string& name) noexcept
{
    setMaterial(Engine::asset().get<Material>(name));
}
void QuadShapeComponent::setMaterial(Reference<Material> material) noexcept
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

void QuadShapeComponent::setCoordinateFactor(float factor) noexcept
{
    m_coordinateFactor = factor;
}

void QuadShapeComponent::generate() noexcept
{
    m_mesh->update(Quad::vertices(
        m_x, m_y,
        m_coordinateFactor
    ));
}