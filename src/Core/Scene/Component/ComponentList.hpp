#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/NonCopyable.hpp>
#include <Core/Utility/ChunkContainer.ipp>
#include <Core/Scene/Component/Component.hpp>

#include <string>
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
        virtual ~IComponentList() = default;
        virtual void destroy(Id id) noexcept = 0;
        virtual std::string identifier() const noexcept = 0;
        virtual Component& getComponent(Id id) const noexcept = 0;
    };

    template<typename C>
    class AXION_CORE_API ComponentList : public IComponentList
    {
    public:
        std::string identifier() const noexcept;
        Component& getComponent(Id id) const noexcept;

    public:
        template<typename... Args>
        Id create(Entity& entity, Args&&... args) noexcept;

        void destroy(Id id) noexcept override;

        C& get(Id id) const noexcept;

        void addCreationCallback(std::function<void(C&)> function);
        void removeCreationCallback(std::function<void(C&)> function);
        void addDestructionCallback(std::function<void(C&)> function);
        void removeDestructionCallback(std::function<void(C&)> function);

    public: 
        using container = ChunkContainer<C, 128>;

        typename container::iterator begin() noexcept;
        typename container::iterator end() noexcept;

    private:
        container m_container;

        std::vector<std::function<void(C&)>> m_createFunctions;
        std::vector<std::function<void(C&)>> m_destroyFunctions;    
    };
}