#include <Core/Prefab/Component/Shape/QuadComponent.hpp>

#include <Core/Renderer/Renderer.hpp>
#include <Core/Asset/AssetManager.hpp>

using namespace ax;

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
    Engine::renderer().setStaticmeshTransform(m_staticmesh, &transform);
    Engine::renderer().setStaticmeshMesh(m_staticmesh, m_mesh);
    m_material = Engine::assets().material(Material::Default);
    Engine::renderer().setStaticmeshMaterial(m_staticmesh, m_material->getHandle());
}
QuadComponent::~QuadComponent()
{
    Engine::renderer().destroyStaticmesh(m_staticmesh);
    Engine::renderer().destroyMesh(m_mesh);
}

void QuadComponent::setMaterial(std::nullptr_t ptr) noexcept
{
    m_material.reset();
    Engine::renderer().setStaticmeshMaterial(m_staticmesh, 0);
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

        Engine::renderer().setStaticmeshMaterial(m_staticmesh, m_material->getHandle());
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
    Engine::renderer().updateMesh(m_mesh, 
        Quad::vertices(
            m_x, m_y,
            m_coordinateFactor
        )
    );
}