#pragma once

#include <Core/Builder/ComponentFactory.hpp>

namespace ax
{
    template<typename C>
    void ComponentFactory<C>::add(Entity& entity, const Json& json) noexcept
    {
        entity.addComponent<C>(json);
    }
    template<typename C>
    void ComponentFactory<C>::remove(Entity& entity) noexcept
    {
        entity.removeComponent<C>();
    }
}