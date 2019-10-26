#pragma once

#include <Core/Scene/GameMode/GameModeManager.hpp>

namespace ax
{
    template<typename G>
    void GameModeManager::set() noexcept
    {
        if(hasNext()) return;
        m_nextGameMode = std::make_unique<G>();
    }
    template<typename G>
    G& GameModeManager::get() const noexcept
    {
        return static_cast<G&>(*m_gameMode.get());
    }
}