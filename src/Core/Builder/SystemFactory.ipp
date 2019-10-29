#pragma once

#include <Core/Builder/SystemFactory.hpp>
#include <Core/Scene/System/SystemManager.ipp>

namespace ax
{
    template<typename C>
    void SystemFactory<C>::add() noexcept
    {
        Engine::scene().system.add<C>();
    }
    template<typename C>
    void SystemFactory<C>::remove() noexcept
    {
        Engine::scene().system.remove<C>();
    }
}