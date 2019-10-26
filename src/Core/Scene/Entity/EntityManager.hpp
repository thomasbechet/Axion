#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/NonCopyable.hpp>
#include <Core/Scene/Entity/Entity.hpp>

#include <unordered_map>
#include <vector>
#include <array>
#include <memory>

namespace ax
{
    class AXION_CORE_API EntityManager : public NonCopyable
    {
    public:
        static constexpr unsigned ENTITY_CHUNK_SIZE = 128;
        using Chunk = std::array<std::pair<Entity, bool>, ENTITY_CHUNK_SIZE>;

    public:
        Entity& create() noexcept;
        Entity& create(const std::string& name) noexcept;

        void destroy(Entity& entity) noexcept;
        void destroy(const std::string& name) noexcept;

        Entity& get(const std::string& name) noexcept;

    private:
        std::vector<std::unique_ptr<Chunk>> m_chunks;
        std::vector<unsigned> m_free;
        unsigned m_size = 0;

        std::unordered_map<std::string, std::reference_wrapper<Entity>> m_tagTable;
    };
}