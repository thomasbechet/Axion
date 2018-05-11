#pragma once

////////////////
//HEADERS
////////////////
#include <unordered_map>
#include <vector>
#include <array>
#include <Core/Export.hpp>
#include <Core/Utility/NonCopyable.hpp>
#include <Core/Entity/Entity.hpp>

namespace ax
{
    constexpr unsigned ENTITY_CHUNK_SIZE = 128;

    class AXION_CORE_API EntityManager : public NonCopyable
    {
    public:
        using Chunk = std::array<std::pair<Entity, bool>, ENTITY_CHUNK_SIZE>;

    public:
        EntityManager(ComponentManager& manager);

        Entity& createEntity() noexcept;
        Entity& createEntity(std::string name) noexcept;

        void destroyEntity(Entity& entity) noexcept;
        void destroyEntity(std::string& name) noexcept;

        Entity& getEntity(std::string& name) noexcept;

    private:
        std::vector<std::unique_ptr<Chunk>> m_entities;
        std::vector<unsigned> m_free;
        unsigned m_size = 0;

        std::unordered_map<std::string, Entity*> m_tagTable;
        ComponentManager& m_componentManager;
    };
}