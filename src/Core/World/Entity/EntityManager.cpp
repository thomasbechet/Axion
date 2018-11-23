#include <Core/World/Entity/EntityManager.hpp>

using namespace ax;

EntityManager::EntityManager(ComponentManager& manager) : m_componentManager(manager){}

Entity& EntityManager::create() noexcept
{
    if(!m_free.empty())
    {
        unsigned back = m_free.back();
        m_free.pop_back();
        m_entities.at(back / ENTITY_CHUNK_SIZE)->at(back % ENTITY_CHUNK_SIZE).second = true;

        return m_entities.at(back / ENTITY_CHUNK_SIZE)->at(back % ENTITY_CHUNK_SIZE).first;
    }
    else
    {
        m_size++;

        if((m_size / ENTITY_CHUNK_SIZE) + 1 > m_entities.size()) //Need to allocate a new chunk
        {
            std::cout << "allocate" << std::endl;
            m_entities.emplace_back(std::make_unique<Chunk>());
        }

        unsigned id = m_size - 1;
        
        m_entities.at(id / ENTITY_CHUNK_SIZE)->at(id % ENTITY_CHUNK_SIZE).second = true; //Initialisation
        m_entities.at(id / ENTITY_CHUNK_SIZE)->at(id % ENTITY_CHUNK_SIZE).first.m_id = id; //Initialisation

        std::cout << "inserted id: " << id << std::endl;

        return m_entities.at(m_size / ENTITY_CHUNK_SIZE)->at(m_size % ENTITY_CHUNK_SIZE).first;
    }
}
Entity& EntityManager::create(std::string name) noexcept
{
    Entity& entity = create();
    m_tagTable[name] = &entity;

    return entity;
}

void EntityManager::destroy(Entity& entity) noexcept
{
    unsigned id = entity.m_id;
    std::cout << "destroyed id: " << id << std::endl;
    m_entities.at(id / ENTITY_CHUNK_SIZE)->at(id % ENTITY_CHUNK_SIZE).first.removeAll();
    m_entities.at(id / ENTITY_CHUNK_SIZE)->at(id % ENTITY_CHUNK_SIZE).second = false;
    m_free.emplace_back(id);
}
void EntityManager::destroy(std::string& name) noexcept
{
    destroy(*m_tagTable[name]);
}

Entity& EntityManager::get(std::string& name) noexcept
{
    return *m_tagTable[name];
}