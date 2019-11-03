#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Utility/NonCopyable.hpp>

#include <array>
#include <memory>
#include <vector>

namespace ax
{
    template<typename T, size_t ChunkSize>
    class AXION_CORE_API ChunkContainer : public NonCopyable
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

        void clear() noexcept;

        size_t size() const noexcept;

    private:
        std::vector<Chunk*> m_chunks;
        std::vector<Id> m_free;
        size_t m_length = 0;
        size_t m_size = 0;

        std::allocator<Chunk> m_allocator;

    public:
        class ChunkContainerIterator
        {
        public:
            using type = T;
            using reference = T&;
            using pointer = T*;

            ChunkContainerIterator(ChunkContainer& chunk, Id position, T* ptr);

            reference operator*();
            pointer operator->();

            ChunkContainerIterator& operator++();
            
            bool operator==(const ChunkContainerIterator& it);
            bool operator!=(const ChunkContainerIterator& it);
        
        private:
            ChunkContainer& m_container;
            T* m_ptr; 
            Id m_position;
        };

    public:
        using iterator = ChunkContainerIterator;
        friend class ChunkContainerIterator;

        iterator begin() noexcept;
        iterator end() noexcept;

    private:
        T* nextId(Id& id) const noexcept;
    };
}