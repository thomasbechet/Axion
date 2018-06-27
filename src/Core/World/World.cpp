#include <Core/World/World.hpp>

#include <Core/World/Entity/EntityManager.hpp>
#include <Core/World/Entity/ComponentManager.hpp>

using namespace ax;

World::World()
{
    m_componentManager = new ComponentManager();
    m_entityManager = new EntityManager(*m_componentManager);
}
World::~World()
{
    delete m_entityManager;
    delete m_componentManager;
}

EntityManager& World::entities() noexcept
{
    return *m_entityManager;
}
ComponentManager& World::components() noexcept
{
    return *m_componentManager;
}