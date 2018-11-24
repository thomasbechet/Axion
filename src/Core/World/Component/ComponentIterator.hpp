#pragma once

//////////////
//HEADERS
//////////////
#include <Core/Export.hpp>
#include <Core/World/Component/ComponentList.hpp>

namespace ax
{
    template<typename C>
    class AXION_CORE_API ComponentIterator
    {
    public:
        friend class ComponentList<C>;

    public:
        ComponentIterator(const ComponentList<C>& list, size_t start, size_t end) : m_start(start), m_end(end), m_list(list)
        {
            m_index = start;
        }

        bool next() noexcept
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

        C* operator->() noexcept
        {
            return m_current;
        }

    private:
        size_t m_index;
        size_t m_start;
        size_t m_end;
        C* m_current = nullptr;
        const ComponentList<C>& m_list;
    };
}