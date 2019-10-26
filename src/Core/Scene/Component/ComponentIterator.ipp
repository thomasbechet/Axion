#pragma once

#include <Core/Scene/Component/ComponentIterator.hpp>

namespace ax
{
    template<typename C>
    ComponentIterator<C>::ComponentIterator(const ComponentList<C>& list, size_t start, size_t end) : m_start(start), m_end(end), m_list(list)
    {
        m_index = start;
    }

    template<typename C>
    bool ComponentIterator<C>::next() noexcept
    {
        while(true)
        {
            if(m_index >= m_end) return false;
            if(m_list.m_chunks.at(m_index / COMPONENT_CHUNK_SIZE)->at(m_index % COMPONENT_CHUNK_SIZE).second) break;
            m_index++; //Next
        }

        m_current = &m_list.get(m_index);
        m_index++; //Increase for the next loop

        return true;
    }

    template<typename C>
    C* ComponentIterator<C>::operator->() noexcept
    {
        return m_current;
    }
}