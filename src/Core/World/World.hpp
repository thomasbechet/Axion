#pragma once

////////////////////////
//HEADERS
////////////////////////
#include <Core/Export.hpp>
#include <Core/Context/GameMode.hpp>
#include <Core/Context/GameState.hpp>

#include <memory>

namespace ax
{
    class EntityManager;
    class ComponentManager;
    class GameMode;
    class GameState;

    class AXION_CORE_API World
    {
    public:
        friend class Game;

    public:
        World();
        ~World();

        EntityManager& entities() noexcept;
        ComponentManager& components() noexcept;

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
        /*template<typename G>
        void setGameState() noexcept
        {
            
        }
        template<typename G>
        G& getGameState() const noexcept
        {

        }
        GameState& getGameState() const noexcept;*/

    
    private:
        EntityManager* m_entityManager;
        ComponentManager* m_componentManager;

        std::unique_ptr<GameMode> m_gameMode;
        GameMode* m_nextGameMode = nullptr;

        std::unique_ptr<GameState> m_gameState;
    };
}