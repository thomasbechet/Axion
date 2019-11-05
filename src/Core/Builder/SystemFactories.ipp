#pragma once

#include <Core/Builder/SystemFactories.hpp>

namespace ax
{
    template<typename S>
    void SystemFactories::record() noexcept
    {
        m_factories[S::identifier] = std::make_unique<SystemFactory<S>>();
    }
    template<typename S>
    void SystemFactories::unrecord() noexcept
    {
        m_factories.erase(S::identifier);
    }
    template<typename S>
    ISystemFactory& SystemFactories::get() noexcept
    {
        return *m_factories.at(S::identifier).get();
    }
}