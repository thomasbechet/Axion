#pragma once

#include <Core/Scene/Component/ComponentList.hpp>

namespace ax
{
    template<typename C>
    std::string ComponentList<C>::identifier() const noexcept
    {
        return C::identifier;
    }
    template<typename C>
    Component& ComponentList<C>::getComponent(unsigned offset) const noexcept
    {
        return static_cast<Component&>(get(offset));
    }

    template<typename C>
    ComponentList<C>::~ComponentList()
    {
        //Destroy every components
        for(unsigned i = 0; i < m_length; i++)
        {
            if(m_chunks.at(i / COMPONENT_CHUNK_SIZE)->at(i % COMPONENT_CHUNK_SIZE).second)
                m_chunks.at(i / COMPONENT_CHUNK_SIZE)->at(i % COMPONENT_CHUNK_SIZE).first.~C();
        }
        m_length = 0;

        //Release memory
        for(auto& it : m_chunks)
            m_allocator.deallocate(it, 1);
    }

    template<typename C>
    template<typename... Args>
    unsigned ComponentList<C>::create(const Entity& entity, Args&&... args) noexcept
    {
        if(!m_free.empty()) //Free spaces
        {
            unsigned back = m_free.back();
            m_free.pop_back();
            m_chunks.at(back / COMPONENT_CHUNK_SIZE)->at(back % COMPONENT_CHUNK_SIZE).second = true;
            new (&m_chunks.at(back / COMPONENT_CHUNK_SIZE)->at(back % COMPONENT_CHUNK_SIZE).first) C(entity, args...);

            return back;
        }
        else
        {
            m_length++;

            if((m_length / COMPONENT_CHUNK_SIZE) + 1 > m_chunks.size()) //Need to allocate a new chunk
                m_chunks.push_back(m_allocator.allocate(1));

            unsigned id = m_length - 1;

            m_chunks.at(id / COMPONENT_CHUNK_SIZE)->at(id % COMPONENT_CHUNK_SIZE).second = true;
            new (&m_chunks.at(id / COMPONENT_CHUNK_SIZE)->at(id % COMPONENT_CHUNK_SIZE).first) C(entity, args...);

            return id;
        }
    }

    template<typename C>
    void ComponentList<C>::destroy(unsigned offset) noexcept
    {
        m_chunks.at(offset / COMPONENT_CHUNK_SIZE)->at(offset % COMPONENT_CHUNK_SIZE).second = false;
        m_chunks.at(offset / COMPONENT_CHUNK_SIZE)->at(offset % COMPONENT_CHUNK_SIZE).first.~C();
        
        if(offset + 1 == m_length)
        {
            m_length--;
        }
        else
        {
            m_free.emplace_back(offset);
        }
    }

    template<typename C>
    C& ComponentList<C>::get(unsigned offset) const noexcept
    {
        if(offset >= m_length)
            Engine::interrupt("Tried to access non valid component <" + C::identifier + "> from list with [id=" + std::to_string(offset) + "]");

        return m_chunks.at(offset / COMPONENT_CHUNK_SIZE)->at(offset % COMPONENT_CHUNK_SIZE).first;
    }

    template<typename C>
    unsigned ComponentList<C>::size() const noexcept
    {
        return m_length - m_free.size();
    }
    template<typename C>
    unsigned ComponentList<C>::free() const noexcept
    {
        return m_free.size();
    }
    template<typename C>
    unsigned ComponentList<C>::length() const noexcept
    {
        return m_length;
    }
    template<typename C>
    Memory ComponentList<C>::memory() const noexcept
    {
        return m_chunks.size() * sizeof(Chunk);
    }

    template<typename C>
    ComponentIterator<C> ComponentList<C>::iterator() const noexcept
    {
        return ComponentIterator<C>(*this, 0, m_length);
    }

    template<typename C>
    void ComponentList<C>::addCreationCallback(std::function<void(C&)> function)
    {
        m_createFunctions.emplace_back(function);
    }
    template<typename C>
    void ComponentList<C>::removeCreationCallback(std::function<void(C&)> function)
    {
        m_createFunctions.erase(std::remove_if(
            m_createFunctions.begin(),
            m_createFunctions.end(),
            [&](const std::function<void(C&)>& f){
                return f.target() == function.target();
            }
        ), m_createFunctions.end());
    }
    template<typename C>
    void ComponentList<C>::addDestructionCallback(std::function<void(C&)> function)
    {
        m_destroyFunctions.emplace_back(function);
    }
    template<typename C>
    void ComponentList<C>::removeDestructionCallback(std::function<void(C&)> function)
    {
        m_destroyFunctions.erase(std::remove_if(
            m_destroyFunctions.begin(),
            m_destroyFunctions.end(),
            [&](const std::function<void(C&)>& f){
                return f.target() == function.target();
            }
        ), m_destroyFunctions.end());
    }
}