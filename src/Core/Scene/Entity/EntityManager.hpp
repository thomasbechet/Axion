#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/NonCopyable.hpp>
#include <Core/Utility/ChunkContainer.ipp>
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
        Entity& create() noexcept;
        Entity& create(const std::string& name) noexcept;

        void destroy(Entity& entity) noexcept;
        void destroy(const std::string& name) noexcept;
        void destroyAll() noexcept;

        Entity& get(const std::string& name) noexcept;

    private:
        ChunkContainer<Entity, 64> m_chunks;

        std::unordered_map<std::string, std::reference_wrapper<Entity>> m_tagTable;
    };
}