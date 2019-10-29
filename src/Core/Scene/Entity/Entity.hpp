#pragma once

#include <Core/Export.hpp>
#include <Core/Scene/Component/Component.hpp>
#include <Core/Utility/Json.hpp>
#include <Core/Utility/Types.hpp>

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

        void addComponent(const std::string& identifier, const Json& json = {}) noexcept;

        template<typename C>
        void removeComponent() noexcept;

        void removeComponent(const std::string& identifier) noexcept;

        void removeAllComponents() noexcept;

        template<typename C>
        C& getComponent() const noexcept;

        template<typename C>
        bool hasComponent() const noexcept;

        bool hasComponent(const std::string& identifier) const noexcept;

        std::vector<std::reference_wrapper<Component>> getComponents() const noexcept;
        std::vector<std::string> getComponentIdentifiers() const noexcept;

    private:
        std::unordered_map<std::string, ComponentHandle> m_handles;
        Id m_id = 0;
    };
}