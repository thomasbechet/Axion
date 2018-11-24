#include <Core/World/Entity/EntityManager.hpp>

using namespace ax;

EntityManager::EntityManager(ComponentManager& manager) : m_componentManager(manager){}
EntityManager::~EntityManager()
{
    for(auto& it : m_chunks)
        m_allocator.deallocate(it, 1);
}

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
            m_chunks.push_back(m_allocator.allocate(1));

        unsigned id = m_size - 1;
        
        m_chunks.at(id / ENTITY_CHUNK_SIZE)->at(id % ENTITY_CHUNK_SIZE).second = true; //Initialisation
        m_chunks.at(id / ENTITY_CHUNK_SIZE)->at(id % ENTITY_CHUNK_SIZE).first.m_id = id; //Initialisation

        return m_chunks.at(id / ENTITY_CHUNK_SIZE)->at(id % ENTITY_CHUNK_SIZE).first;
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
    std::cout << "destroy entity: " << entity.m_id << std::endl;
    unsigned id = entity.m_id;
    m_chunks.at(id / ENTITY_CHUNK_SIZE)->at(id % ENTITY_CHUNK_SIZE).first.removeAll();
    m_chunks.at(id / ENTITY_CHUNK_SIZE)->at(id % ENTITY_CHUNK_SIZE).second = false;
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