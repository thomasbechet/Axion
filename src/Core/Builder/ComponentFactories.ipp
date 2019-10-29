#pragma once

#include <Core/Builder/ComponentFactories.hpp>

namespace ax
{
    template<typename C>
    void ComponentFactories::record() noexcept
    {
        m_factories[C::identifier] = std::make_unique<ComponentFactory<C>>();
    }
    template<typename C>
    void ComponentFactories::unrecord() noexcept
    {
        m_factories.erase(C::identifier);
    }
    template<typename C>
    IComponentFactory& ComponentFactories::get()
    {
        return *m_factories[C::identifier].get();
    }
}