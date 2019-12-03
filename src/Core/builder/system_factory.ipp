#pragma once

#include <core/builder/system_factory.hpp>
#include <core/scene/scene_module.hpp>
#include <core/scene/system/system_manager.ipp>

namespace ax
{
    template<typename type>
    void system_factory<type>::add() noexcept
    {
        engine::scene().system.add<C>();
    }
    template<typename type>
    void system_factory<type>::remove() noexcept
    {
        engine::scene().system.remove<type>();
    }
}