#include <Core/Prefab/Component/Shape/QuadComponent.hpp>

#include <Core/Renderer/Renderer.hpp>
#include <Core/Asset/AssetManager.hpp>

using namespace ax;

const std::string QuadComponent::name = "Quad";

QuadComponent::QuadComponent(const Entity& entity, float x, float y, float factor) :
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
    m_material = Engine::assets().material(Material::Default);
    m_staticmesh->setMaterial(m_material->getHandle());
}
QuadComponent::~QuadComponent()
{
    Engine::renderer().destroyStaticmesh(m_staticmesh);
    Engine::renderer().destroyMesh(m_mesh);
}

void QuadComponent::setMaterial(std::nullptr_t ptr) noexcept
{
    m_material.reset();
    m_staticmesh->setMaterial(nullptr);
}
void QuadComponent::setMaterial(std::string name) noexcept
{
    setMaterial(Engine::assets().material(name));
}
void QuadComponent::setMaterial(AssetReference<Material> material) noexcept
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

void QuadComponent::setCoordinateFactor(float factor) noexcept
{
    m_coordinateFactor = factor;
}

void QuadComponent::generate() noexcept
{
    m_mesh->update(Quad::vertices(
        m_x, m_y,
        m_coordinateFactor
    ));
}