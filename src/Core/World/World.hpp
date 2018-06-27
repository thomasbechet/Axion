#pragma once

////////////////////////
//HEADERS
////////////////////////
#include <Core/Export.hpp>

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

        template<typename G>
        void setGameMode()
        {
            
        }
        template<typename G>
        void setGameState()
        {

        }

        template<typename G>
        G& getGameMode()
        {

        }
        template<typename G>
        G& getGameState()
        {

        }

    
    private:
        EntityManager* m_entityManager;
        ComponentManager* m_componentManager;
        GameMode* m_gameMode;
        GameState* m_gameState;
    };
}