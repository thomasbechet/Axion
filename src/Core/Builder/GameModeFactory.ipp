#pragma once

#include <Core/Builder/GameModeFactory.hpp>
#include <Core/Context/Engine.hpp>
#include <Core/Scene/SceneModule.hpp>

namespace ax
{
    template<typename C>
    void GameModeFactory<C>::set() noexcept
    {
        Engine::scene().gamemode.set<C>();
    }
}