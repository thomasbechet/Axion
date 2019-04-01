#include <Core/Prefab/Component/Shape/RectangleComponent.hpp>

#include <Core/Renderer/Renderer.hpp>
#include <Core/Asset/AssetManager.hpp>

using namespace ax;

const std::string RectangleComponent::name = "Rectangle";

RectangleComponent::RectangleComponent(const Entity& entity,
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
    m_material = Engine::assets().material(Material::Default);
    m_staticmesh->setMaterial(m_material->getHandle());
}
RectangleComponent::~RectangleComponent()
{
    Engine::renderer().destroyStaticmesh(m_staticmesh);
    Engine::renderer().destroyMesh(m_mesh);
}

void RectangleComponent::setMaterial(std::nullptr_t ptr) noexcept
{
    m_material.reset();
    m_staticmesh->setMaterial(nullptr);
}
void RectangleComponent::setMaterial(std::string name) noexcept
{
    setMaterial(Engine::assets().material(name));
}
void RectangleComponent::setMaterial(AssetReference<Material> material) noexcept
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

void RectangleComponent::setCoordinateFactor(float factor) noexcept
{
    m_coordinateFactor = factor;
}

void RectangleComponent::generate() noexcept
{
    m_mesh->update(Rectangle::vertices(
        m_xMin, m_xMax,
        m_yMin, m_yMax,
        m_zMin, m_zMax,
        m_coordinateFactor
    ));
}