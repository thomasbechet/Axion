#include <Core/World/World.hpp>

#include <Core/World/Entity/EntityManager.hpp>
#include <Core/World/Entity/ComponentManager.hpp>

using namespace ax;

World::World()
{
    m_gameMode = std::make_unique<GameMode>();

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

GameMode& World::getGameMode() const noexcept
{
    return *m_gameMode.get();
}

bool World::hasNextGameMode() const noexcept
{
    return (m_nextGameMode != nullptr);
}
void World::nextGameMode() noexcept
{
    if(!hasNextGameMode()) return;

    m_gameMode.reset(m_nextGameMode);
    m_nextGameMode = nullptr;
}