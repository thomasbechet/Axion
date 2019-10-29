#include <Core/Scene/Entity/EntityManager.hpp>

using namespace ax;

Entity& EntityManager::create() noexcept
{
    if(!m_free.empty())
    {
        unsigned back = m_free.back();
        m_free.pop_back();
        m_chunks.at(back / ENTITY_CHUNK_SIZE)->at(back % ENTITY_CHUNK_SIZE).second = true;

        return m_chunks.at(back / ENTITY_CHUNK_SIZE)->at(back % ENTITY_CHUNK_SIZE).first;
    }
    else
    {
        m_size++;

        if((m_size / ENTITY_CHUNK_SIZE) + 1 > m_chunks.size()) //Need to allocate a new chunk
        {
            //Need to construct chunk to allocate vectors memory
            m_chunks.emplace_back(std::make_unique<Chunk>());
        }

        unsigned id = m_size - 1;
        
        m_chunks.at(id / ENTITY_CHUNK_SIZE)->at(id % ENTITY_CHUNK_SIZE).second = true; //Initialisation
        m_chunks.at(id / ENTITY_CHUNK_SIZE)->at(id % ENTITY_CHUNK_SIZE).first.m_id = id; //Initialisation

        return m_chunks.at(id / ENTITY_CHUNK_SIZE)->at(id % ENTITY_CHUNK_SIZE).first;
    }
}
Entity& EntityManager::create(const std::string& name) noexcept
{
    Entity& entity = create();
    m_tagTable.emplace(name, entity);

    return entity;
}

void EntityManager::destroy(Entity& entity) noexcept
{
    unsigned id = entity.m_id;
    m_chunks.at(id / ENTITY_CHUNK_SIZE)->at(id % ENTITY_CHUNK_SIZE).first.removeAllComponents();
    m_chunks.at(id / ENTITY_CHUNK_SIZE)->at(id % ENTITY_CHUNK_SIZE).second = false;
    m_free.emplace_back(id);
}
void EntityManager::destroy(const std::string& name) noexcept
{
    destroy(m_tagTable.at(name).get());
}

Entity& EntityManager::get(const std::string& name) noexcept
{
    return m_tagTable.at(name).get();
}