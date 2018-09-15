#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>
#include <Core/Context/Engine.hpp>
#include <Core/Utility/NonCopyable.hpp>
#include <Core/Utility/Memory.hpp>

#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <functional>

#include <iostream>

namespace ax
{
    template<typename C>
    class ComponentIterator;

    class AXION_CORE_API IComponentList : public NonCopyable
    {
    public:
        virtual ~IComponentList() = default; //Make sure the component list will be released
        virtual void destroy(unsigned offset) noexcept = 0;
        virtual std::string name() const noexcept = 0;
    };

    constexpr unsigned COMPONENT_CHUNK_SIZE = 128;

    template<typename C>
    class AXION_CORE_API ComponentList : public IComponentList
    {
    public:
        friend class ComponentIterator<C>;
        using Chunk = std::pair<C, bool>;

    public:
        std::string name() const noexcept
        {
            return C::name();
        }

    public:
        template<typename... Args>
        unsigned create(Args&&... args) noexcept
        {
            if(!m_free.empty()) //Free spaces
            {
                unsigned back = m_free.back();
                m_free.pop_back();
                m_components[back / COMPONENT_CHUNK_SIZE][back % COMPONENT_CHUNK_SIZE].second = true;
                new (&m_components[back / COMPONENT_CHUNK_SIZE][back % COMPONENT_CHUNK_SIZE].first) C(args...);

                return back;
            }
            else
            {
                m_length++;

                if((m_length / COMPONENT_CHUNK_SIZE) + 1 > m_components.size()) //Need to allocate a new chunk
                    m_components.emplace_back(static_cast<Chunk*>(operator new(sizeof(Chunk) * COMPONENT_CHUNK_SIZE)));

                unsigned id = m_length - 1;

                m_components[id / COMPONENT_CHUNK_SIZE][id % COMPONENT_CHUNK_SIZE].second = true;
                new (&m_components[id / COMPONENT_CHUNK_SIZE][id % COMPONENT_CHUNK_SIZE].first) C(args...);

                return id;
            }
        }

        void destroy(unsigned offset) noexcept override
        {
            m_components[offset / COMPONENT_CHUNK_SIZE][offset % COMPONENT_CHUNK_SIZE].second = false;
            m_components[offset / COMPONENT_CHUNK_SIZE][offset % COMPONENT_CHUNK_SIZE].first.~C();
            
            if(offset + 1 == m_length)
            {
                m_length--;
            }
            else
            {
                m_free.emplace_back(offset);
            }
        }

        C& get(unsigned offset) const noexcept
        {
            if(offset >= m_length)
                Engine::interrupt("Tried to access non valid component <" + C::name() + "> from list with [id=" + std::to_string(offset) + "]");

            return m_components[offset / COMPONENT_CHUNK_SIZE][offset % COMPONENT_CHUNK_SIZE].first;
        }

        unsigned size() const noexcept
        {
            return m_length - m_free.size();
        }
        unsigned free() const noexcept
        {
            return m_free.size();
        }
        unsigned length() const noexcept
        {
            return m_length;
        }

        Memory memory() const noexcept
        {
            return m_components.size() * COMPONENT_CHUNK_SIZE * sizeof(Chunk);
        }

        ComponentIterator<C> iterator() const noexcept
        {
            return ComponentIterator<C>(*this, 0, m_length);
        }

        void addCreationCallback(std::function<void(C&)> function)
        {
            m_createFunctions.emplace_back(function);
        }
        void removeCreationCallback(std::function<void(C&)> function)
        {
            m_createFunctions.erase(std::remove_if(
                m_createFunctions.begin(),
                m_createFunctions.end(),
                [&](const std::function<void(C&)>& f){
                    return f.target() == function.target();
                }
            ), m_createFunctions.end());
        }
        void addDestructionCallback(std::function<void(C&)> function)
        {
            m_destroyFunctions.emplace_back(function);
        }
        void removeDestructionCallback(std::function<void(C&)> function)
        {
            m_destroyFunctions.erase(std::remove_if(
                m_destroyFunctions.begin(),
                m_destroyFunctions.end(),
                [&](const std::function<void(C&)>& f){
                    return f.target() == function.target();
                }
            ), m_destroyFunctions.end());
        }

    private:
        std::vector<Chunk*> m_components;
        std::vector<unsigned> m_free;
        unsigned m_length = 0;

        std::vector<std::function<void(C&)>> m_createFunctions;
        std::vector<std::function<void(C&)>> m_destroyFunctions;    
    };
}