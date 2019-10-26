#pragma once

#include <Core/Export.hpp>
#include <Core/Context/Engine.hpp>
#include <Core/Utility/NonCopyable.hpp>
#include <Core/Utility/Memory.hpp>

#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <functional>

namespace ax
{
    template<typename C>
    class ComponentIterator;
    class Entity;

    class AXION_CORE_API IComponentList : public NonCopyable
    {
    public:
        virtual ~IComponentList() = default; //Make sure the component list will be released
        virtual void destroy(unsigned offset) noexcept = 0;
        virtual std::string type() const noexcept = 0;
    };

    constexpr unsigned COMPONENT_CHUNK_SIZE = 128;

    template<typename C>
    class AXION_CORE_API ComponentList : public IComponentList
    {
    public:
        friend class ComponentIterator<C>;
        using Chunk = std::array<std::pair<C, bool>, COMPONENT_CHUNK_SIZE>;

    public:
        std::string type() const noexcept;

    public:
        ~ComponentList();

        template<typename... Args>
        unsigned create(const Entity& entity, Args&&... args) noexcept;

        void destroy(unsigned offset) noexcept override;

        C& get(unsigned offset) const noexcept;

        unsigned size() const noexcept;
        unsigned free() const noexcept;
        unsigned length() const noexcept;
        Memory memory() const noexcept;

        ComponentIterator<C> iterator() const noexcept;

        void addCreationCallback(std::function<void(C&)> function);
        void removeCreationCallback(std::function<void(C&)> function);
        void addDestructionCallback(std::function<void(C&)> function);
        void removeDestructionCallback(std::function<void(C&)> function);

    private:
        std::vector<Chunk*> m_chunks;
        std::allocator<Chunk> m_allocator;
        std::vector<unsigned> m_free;
        unsigned m_length = 0;

        std::vector<std::function<void(C&)>> m_createFunctions;
        std::vector<std::function<void(C&)>> m_destroyFunctions;    
    };
}