#include <Core/Entity/EntityManager.hpp>

using namespace ax;

EntityManager::EntityManager(ComponentManager& manager) : m_componentManager(manager){}

Entity& EntityManager::createEntity() noexcept
{
    if(!m_free.empty())
    {
        unsigned back = m_free.back();
        m_free.pop_back();
        (*m_entities[back / ENTITY_CHUNK_SIZE].get())[back % ENTITY_CHUNK_SIZE].second = true;

        return (*m_entities[back / ENTITY_CHUNK_SIZE].get())[back % ENTITY_CHUNK_SIZE].first;
    }
    else
    {
        m_size++;

        if((m_size / ENTITY_CHUNK_SIZE) + 1 > m_entities.size()) //Need to allocate a new chunk
        {
            m_entities.emplace_back(std::make_unique<Chunk>());
        }

        unsigned id = m_size - 1;
        
        (*m_entities[id / ENTITY_CHUNK_SIZE].get())[id % ENTITY_CHUNK_SIZE].second = true; //Initialisation
        (*m_entities[id / ENTITY_CHUNK_SIZE].get())[id % ENTITY_CHUNK_SIZE].first.m_id = id; //Initialisation

        return (*m_entities[m_size / ENTITY_CHUNK_SIZE].get())[m_size % ENTITY_CHUNK_SIZE].first;
    }
}
Entity& EntityManager::createEntity(std::string name) noexcept
{
    Entity& entity = createEntity();
    m_tagTable[name] = &entity;

    return entity;
}

void EntityManager::destroyEntity(Entity& entity) noexcept
{
    unsigned id = entity.m_id;
    (*m_entities[id / ENTITY_CHUNK_SIZE].get())[id % ENTITY_CHUNK_SIZE].first.removeAll();
    (*m_entities[id / ENTITY_CHUNK_SIZE].get())[id % ENTITY_CHUNK_SIZE].second = false;
    m_free.emplace_back(id);
}
void EntityManager::destroyEntity(std::string& name) noexcept
{
    destroyEntity(*m_tagTable[name]);
}

Entity& EntityManager::getEntity(std::string& name) noexcept
{
    return *m_tagTable[name];
}