#pragma once

#include <core/builder/gamemode_factory.hpp>
#include <core/engine/engine.hpp>
#include <core/scene/scene_module.hpp>

namespace ax
{
    template<typename type>
    void gamemode_factory<type>::set() noexcept
    {
        engine::scene().gamemode.set<type>();
    }
}