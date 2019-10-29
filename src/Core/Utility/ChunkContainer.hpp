#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/Types.hpp>

#include <array>
#include <memory>
#include <vector>

namespace ax
{
    template<typename T, size_t ChunkSize>
    class AXION_CORE_API ChunkContainer
    {
    public:
        using Pair = std::pair<bool, T>;
        using Chunk = std::array<Pair, ChunkSize>;

    public:
        ~ChunkContainer();

        template<typename... Args>
        Id add(Args... args) noexcept;
        
        void remove(Id id) noexcept;

        T& get(Id id) const;

        size_t size() const noexcept;

        void clear() noexcept;

    private:
        std::vector<Chunk*> m_chunks;
        std::vector<Id> m_free;
        size_t m_size = 0;
        size_t m_count = 0;

        std::allocator<Chunk> m_allocator;
    };
}