#include <Core/Prefab/Component/Shape/RectangleShapeComponent.hpp>

#include <Core/Asset/AssetModule.ipp>
#include <Core/Renderer/RendererModule.hpp>

using namespace ax;

RectangleShapeComponent::RectangleShapeComponent(const Entity& entity, const Json& json) :
    transform(entity.getComponent<TransformComponent>())
{

}
RectangleShapeComponent::RectangleShapeComponent(const Entity& entity,
        float xMin, float xMax,
        float yMin, float yMax,
        float zMin, float zMax,
        bool smooth,
        float factor
    ) :
    Rectangle(
        xMin, xMax,
        yMin, yMax,
        zMin, zMax
    ),
    transform(entity.getComponent<TransformComponent>()),
    m_coordinateFactor(factor)
{
    //Mesh
    m_mesh = Engine::renderer().createMesh(
        Rectangle::vertices(
            m_xMin, m_xMax,
            m_yMin, m_yMax,
            m_zMin, m_zMax,
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
RectangleShapeComponent::~RectangleShapeComponent()
{
    Engine::renderer().destroyStaticmesh(m_staticmesh);
    Engine::renderer().destroyMesh(m_mesh);
}

void RectangleShapeComponent::setMaterial(std::nullptr_t ptr) noexcept
{
    m_material.reset();
    m_staticmesh->setMaterial(nullptr);
}
void RectangleShapeComponent::setMaterial(const std::string& name) noexcept
{
    setMaterial(Engine::asset().get<Material>(name));
}
void RectangleShapeComponent::setMaterial(AssetReference<Material> material) noexcept
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

void RectangleShapeComponent::setCoordinateFactor(float factor) noexcept
{
    m_coordinateFactor = factor;
}

void RectangleShapeComponent::generate() noexcept
{
    m_mesh->update(Rectangle::vertices(
        m_xMin, m_xMax,
        m_yMin, m_yMax,
        m_zMin, m_zMax,
        m_coordinateFactor
    ));
}