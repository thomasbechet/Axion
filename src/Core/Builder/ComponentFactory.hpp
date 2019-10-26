#pragma once

#include <Core/Export.hpp>
#include <Core/Scene/Entity/Entity.hpp>
#include <Core/Utility/Json.hpp>

namespace ax
{
    class AXION_CORE_API IComponentFactory
    {
    public:
        virtual ~IComponentFactory() = default;
        virtual void create(Entity& entity, const Json& json) noexcept = 0; 
    };

    template<typename C>
    class AXION_CORE_API ComponentFactory : public IComponentFactory
    {
    public:
        void create(const Entity& entity, const Json& json) noexcept override
        {
            entity.addComponent<C>(json);
        }
    };
}