#pragma once

#include <Core/Export.hpp>
#include <Core/Scene/GameMode/GameMode.hpp>

#include <memory>

namespace ax
{
    class AXION_CORE_API GameModeManager
    {
    public:
        friend class ContextModule;

    public:
        GameModeManager();

    public:
        template<typename G>
        void set() noexcept;
        template<typename G>
        G& get() const noexcept;
        GameMode& get() const noexcept;

    private:
        bool hasNext() const noexcept;
        void next() noexcept;

        std::unique_ptr<GameMode> m_gameMode;
        std::unique_ptr<GameMode> m_nextGameMode;
    };
}