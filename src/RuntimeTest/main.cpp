#include <iostream>

#include <Core/Math/Vector.hpp>
#include <Core/Math/Matrix.hpp>
#include <Core/Math/Math.hpp>
#include <Core/Math/Transform.hpp>
#include <Core/Utility/ThreadPool.hpp>
#include <Core/Utility/Timer.hpp>
#include <Core/World/Entity/Entity.hpp>
#include <Core/World/Entity/EntityManager.hpp>
#include <Core/Context/Game.hpp>
#include <Core/Renderer/Renderer.hpp>
#include <Core/World/Entity/ComponentIterator.hpp>
#include <Core/Logger/Logger.hpp>
#include <Core/Utility/Memory.hpp>
#include <Core/Context/GameContext.hpp>
#include <Core/System/System.hpp>
#include <Core/System/SystemManager.hpp>
#include <Core/Input/Input.hpp>

struct Position : public ax::Component
{
    void load(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) noexcept
    {
        x = _x;
        y = _y;
        z = _z;
    }
    void unload()
    {
        
    }
    static std::string name(){return "Position";};

    float x;
    float y;
    float z;
};

struct StaticMesh : public ax::Component
{
    void load(const ax::Entity& e) noexcept
    {
        position = &e.getComponent<Position>();       
    }
    void unload() noexcept 
    {
        
    }
    static std::string name(){return "StaticMesh";}

    ax::Renderer::Id id;
    Position* position;
};



class MyGameState : public ax::GameState
{
public:
    unsigned getCount(){return count;}
    void increment(){count++;}

private:
    unsigned count = 0;
};

class StaticMeshSystem : public ax::System
{
public:
    static std::string name(){return "StaticMeshSystem";}

    void onStart() override
    {
        
    }
    void onUpdate() override
    {
        //m_timer.start();
        //while(m_timer.getElapsedTime().asSeconds() < 1. / 1000.){}
    }
    void onFixedUpdate() override
    {
        m_timer.start();
        while(m_timer.getElapsedTime().asSeconds() < 1. / 140.){}
    }   
    void onStop() override
    {

    }

    ax::Timer m_timer;
};

class LolInput : public ax::Input
{
protected:
    void initialize() noexcept {};
    void terminate() noexcept {};

public:
    ax::KeyboardManager& keyboard() noexcept {};
    ax::MouseManager& mouse() noexcept {};
    ax::JoystickManager& joystick() noexcept {};
};

class MyGameMode : public ax::GameMode
{
public:
    void onStart() override
    {
        ax::Game::systems().add<StaticMeshSystem>();

        LolInput& lol = static_cast<LolInput&>(ax::Game::input());
    }
    void onStop() override
    {
        ax::Game::systems().remove<StaticMeshSystem>();
    }
};



int main(int argc, char* argv[])
{
    ax::Game::initialize();
    ax::Game::world().setGameMode<MyGameMode>();
    ax::Game::engine().start();
    ax::Game::terminate();

    return 0;
}