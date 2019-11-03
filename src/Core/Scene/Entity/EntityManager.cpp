#include <Core/Scene/Entity/EntityManager.hpp>

using namespace ax;

Entity& EntityManager::create() noexcept
{
    Id id = m_chunks.add();
    Entity& entity = m_chunks.get(id);
    entity.m_id = id;

    return entity;
}
Entity& EntityManager::create(const std::string& name) noexcept
{
    Entity& entity = create();
    m_tagTable.emplace(name, entity);

    return entity;
}

void EntityManager::destroy(Entity& entity) noexcept
{
    entity.removeAllComponents();
    m_chunks.remove(entity.m_id);
}
void EntityManager::destroy(const std::string& name) noexcept
{
    destroy(m_tagTable.at(name).get());
}
void EntityManager::destroyAll() noexcept
{
    for(auto& entity : m_chunks)
        entity.removeAllComponents();

    m_chunks.clear();
}

Entity& EntityManager::get(const std::string& name) noexcept
{
    return m_tagTable.at(name).get();
}