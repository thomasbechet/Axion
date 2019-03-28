#pragma once

#include <Core/Export.hpp>
#include <Core/Context/GameMode.hpp>
#include <Core/Context/GameState.hpp>

#include <memory>

namespace ax
{
    class EntityManager;
    class ComponentManager;

    class AXION_CORE_API World
    {
    public:
        friend class EngineContext;

    public:
        World();
        ~World();

    private:
        ComponentManager* m_componentManager;
        EntityManager* m_entityManager;

    public:
        ComponentManager& component;
        EntityManager& entity;

    public:
        template<typename G>
        void setGameMode() noexcept
        {
            if(hasNextGameMode()) return;
            m_nextGameMode = new G();
        }
        template<typename G>
        G& getGameMode() const noexcept
        {
            return static_cast<G&>(*m_gameMode);
        }
        GameMode& getGameMode() const noexcept;

    private:
        bool hasNextGameMode() const noexcept;
        void nextGameMode() noexcept;

    public:
        template<typename G>
        void setGameState() noexcept
        {
            m_gameState.reset(new G());
        }
        template<typename G>
        G& getGameState() const noexcept
        {
            return static_cast<G&>(*m_gameState.get());
        }
        GameState& getGameState() const noexcept;

    
    private:
        std::unique_ptr<GameMode> m_gameMode;
        GameMode* m_nextGameMode = nullptr;

        std::unique_ptr<GameState> m_gameState;
    };
}