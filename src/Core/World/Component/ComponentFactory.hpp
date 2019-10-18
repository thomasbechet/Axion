#pragma once

#include <Core/Export.hpp>
#include <Core/World/Entity/Entity.hpp>

namespace ax
{
    class AXION_CORE_API ComponentFactory
    {
    public:
        virtual void create(Entity& entity) noexcept = 0; 
    };

    template<typename C>
    class AXION_CORE_API ComponentFactoryImpl : public ComponentFactory
    {
    public:
        void create(Entity& entity) noexcept override
        {
            entity.addComponent<C>();
        }
    };
}