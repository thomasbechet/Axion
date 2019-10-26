#pragma once

#include <Core/Export.hpp>
#include <Core/Scene/Component/Component.hpp>

#include <vector>

namespace ax
{
    class AXION_CORE_API Entity
    {
    public:
        friend class EntityManager;

    public:
        template<typename C, typename... Args>
        C& addComponent(Args&&... args) noexcept;

        template<typename C>
        void removeComponent() noexcept;

        void removeAll() noexcept;

        template<typename C>
        C& getComponent() const noexcept;

        template<typename C>
        bool hasComponent() const noexcept;

    private:
        std::vector<ComponentHandle> m_handles;
        unsigned m_id = 0;
    };
}