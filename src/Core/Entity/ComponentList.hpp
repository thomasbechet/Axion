#pragma once

///////////////
//HEADERS
///////////////
#include <memory>
#include <vector>
#include <Core/Export.hpp>
#include <Core/Context/Game.hpp>
#include <Core/Utility/NonCopyable.hpp>
#include <Core/Utility/Memory.hpp>

namespace ax
{
    template<typename C>
    class ComponentIterator;

    class AXION_CORE_API IComponentList : public NonCopyable
    {
    public:
        virtual ~IComponentList() = default; //Make sure the component list will be released
        virtual void destroy(unsigned offset) noexcept = 0;
    };

    constexpr unsigned COMPONENT_CHUNK_SIZE = 128;

    template<typename C>
    class AXION_CORE_API ComponentList : public IComponentList
    {
    public:
        friend class ComponentIterator<C>;
        using Chunk = std::array<std::pair<C, bool>, COMPONENT_CHUNK_SIZE>;

    public:
        template<typename... Args>
        unsigned create(Args&&... args) noexcept
        {
            if(!m_free.empty()) //Free spaces
            {
                unsigned back = m_free.back();
                m_free.pop_back();
                (*m_components[back / COMPONENT_CHUNK_SIZE].get())[back % COMPONENT_CHUNK_SIZE].second = true;
                (*m_components[back / COMPONENT_CHUNK_SIZE].get())[back % COMPONENT_CHUNK_SIZE].first.load(args...);

                return back;
            }
            else
            {
                m_length++;

                if((m_length / COMPONENT_CHUNK_SIZE) + 1 > m_components.size()) //Need to allocate a new chunk
                {
                    m_components.emplace_back(std::make_unique<Chunk>());
                }

                unsigned id = m_length - 1;

                (*m_components[id / COMPONENT_CHUNK_SIZE].get())[id % COMPONENT_CHUNK_SIZE].first.load(args...);
                (*m_components[id / COMPONENT_CHUNK_SIZE].get())[id % COMPONENT_CHUNK_SIZE].second = true;

                return id;
            }
        }

        void destroy(unsigned offset) noexcept override
        {
            (*m_components[offset / COMPONENT_CHUNK_SIZE].get())[offset % COMPONENT_CHUNK_SIZE].first.unload();
            (*m_components[offset / COMPONENT_CHUNK_SIZE].get())[offset % COMPONENT_CHUNK_SIZE].second = false;
            
            if(offset + 1 == m_length)
            {
                m_length--;
            }
            else
            {
                m_free.emplace_back(offset);
            }
        }

        C& get(unsigned offset) noexcept
        {
            if(offset >= m_length)
                Game::interrupt("Tried to access non valid component <" + C::name() + "> from list with [id=" + std::to_string(offset) + "]");

            return (*m_components[offset / COMPONENT_CHUNK_SIZE].get())[offset % COMPONENT_CHUNK_SIZE].first;
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
            return m_components.size() * COMPONENT_CHUNK_SIZE * sizeof(C);
        }

    private:
        std::vector<std::unique_ptr<Chunk>> m_components;
        std::vector<unsigned> m_free;
        unsigned m_length = 0;
    };
}