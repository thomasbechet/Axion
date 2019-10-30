#pragma once

#include <Core/Utility/ChunkContainer.hpp>

namespace ax
{
    template<typename T, size_t ChunkSize>
    ChunkContainer<T, ChunkSize>::~ChunkContainer()
    {
        clear();
    }

    template<typename T, size_t ChunkSize>
    template<typename... Args>
    Id ChunkContainer<T, ChunkSize>::add(Args... args) noexcept
    {
        if(!m_free.empty()) //Free spaces
        {
            Id back = m_free.back();
            m_free.pop_back();
            m_chunks.at(back / ChunkSize)->at(back % ChunkSize).first = true;
            new (&m_chunks.at(back / ChunkSize)->at(back % ChunkSize).second) T(args...);

            m_count++;

            return back;
        }
        else
        {
            m_size++;

            if((m_size / ChunkSize) >= m_chunks.size()) //Need to allocate a new chunk
                m_chunks.emplace_back(m_allocator.allocate(1));

            size_t id = m_size - 1;

            m_chunks.at(id / ChunkSize)->at(id % ChunkSize).first = true;
            new (&m_chunks.at(id / ChunkSize)->at(id % ChunkSize).second) T(args...);

            m_count++;

            return id;
        }
    }
    
    template<typename T, size_t ChunkSize>
    void ChunkContainer<T, ChunkSize>::remove(Id id) noexcept
    {
        Pair& pair = m_chunks.at(id / ChunkSize)->at(id % ChunkSize);
        pair.first = false;
        pair.second.~T();
        
        if(id + 1 == m_size)
            m_size--;
        else
            m_free.emplace_back(id);

        m_count--;
    }

    template<typename T, size_t ChunkSize>
    T& ChunkContainer<T, ChunkSize>::get(Id id) const
    {
        Pair& pair = m_chunks.at(id / ChunkSize)->at(id % ChunkSize);

        if(!pair.first)
            throw std::out_of_range("Tried to access non active object from chunk [id=" + std::to_string(id) + "]");

        return pair.second;
    }

    template<typename T, size_t ChunkSize>
    size_t ChunkContainer<T, ChunkSize>::size() const noexcept
    {
        return m_count;
    }

    template<typename T, size_t ChunkSize>
    void ChunkContainer<T, ChunkSize>::clear() noexcept
    {
        //Destroy every objects
        for(size_t i = 0; i < m_size; i++)
            if(m_chunks.at(i / ChunkSize)->at(i % ChunkSize).first)
                m_chunks.at(i / ChunkSize)->at(i % ChunkSize).second.~T();

        m_size = 0;
        m_count = 0;

        //Release memory
        for(auto& it : m_chunks)
            m_allocator.deallocate(it, 1);
    }
}

namespace ax
{
    template<typename T, size_t ChunkSize>
    ChunkContainer<T, ChunkSize>::
    ChunkContainerIterator::ChunkContainerIterator(ChunkContainer& container, Id position, T* ptr) :
        m_container(container), m_position(position), m_ptr(ptr)
    {

    }

    template<typename T, size_t ChunkSize>
    typename ChunkContainer<T, ChunkSize>::ChunkContainerIterator::reference ChunkContainer<T, ChunkSize>::ChunkContainerIterator::operator*()
    {
        return *m_ptr;
    }
    template<typename T, size_t ChunkSize>
    typename ChunkContainer<T, ChunkSize>::ChunkContainerIterator::pointer ChunkContainer<T, ChunkSize>::ChunkContainerIterator::operator->()
    {
        return m_ptr;
    }

    template<typename T, size_t ChunkSize>
    typename ChunkContainer<T, ChunkSize>::ChunkContainerIterator& ChunkContainer<T, ChunkSize>::ChunkContainerIterator::operator++()
    {
        m_ptr = m_container.nextId(m_position);
        return *this;
    }
    
    template<typename T, size_t ChunkSize>
    bool ChunkContainer<T, ChunkSize>::ChunkContainerIterator::operator==(const ChunkContainerIterator& it)
    {
        return m_position == it.m_position;
    }
    template<typename T, size_t ChunkSize>
    bool ChunkContainer<T, ChunkSize>::ChunkContainerIterator::operator!=(const ChunkContainerIterator& it)
    {
        return m_position != it.m_position;
    }

    template<typename T, size_t ChunkSize>
    typename ChunkContainer<T, ChunkSize>::iterator ChunkContainer<T, ChunkSize>::begin() noexcept
    {
        if(m_size <= 0)
            return ChunkContainer<T, ChunkSize>::ChunkContainerIterator(*this, 0, nullptr);

        Pair& first = m_chunks.at(0 / ChunkSize)->at(0 % ChunkSize);
        if(first.first)
            return ChunkContainer<T, ChunkSize>::ChunkContainerIterator(*this, 0, &first.second);

        Id id = 0;
        T* ptr = nextId(id);
        if(ptr)
            return ChunkContainer<T, ChunkSize>::ChunkContainerIterator(*this, id, ptr);
        else
            return end();
    }
    template<typename T, size_t ChunkSize>
    typename ChunkContainer<T, ChunkSize>::iterator ChunkContainer<T, ChunkSize>::end() noexcept
    {
        return ChunkContainer<T, ChunkSize>::ChunkContainerIterator(*this, m_size, nullptr);
    }

    template<typename T, size_t ChunkSize>
    T* ChunkContainer<T, ChunkSize>::nextId(Id& id) const noexcept
    {
        while(true)
        {
            id++;
            if(id >= m_size) break;
            Pair& pair = m_chunks.at(id / ChunkSize)->at(id % ChunkSize);
            if(pair.first) return &pair.second;
        }

        return nullptr;
    }
}