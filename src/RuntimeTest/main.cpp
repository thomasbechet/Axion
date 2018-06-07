#include <iostream>

#include <Core/Math/Vector.hpp>
#include <Core/Math/Matrix.hpp>
#include <Core/Math/Math.hpp>
#include <Core/Math/Transform.hpp>
#include <Core/Utility/ThreadPool.hpp>
#include <Core/Utility/Timer.hpp>
#include <Core/Entity/ComponentManager.hpp>
#include <Core/Entity/Entity.hpp>
#include <Core/Entity/EntityManager.hpp>
#include <Core/Context/Game.hpp>
#include <Core/CoreSystems/Renderer.hpp>
#include <Core/Entity/ComponentIterator.hpp>
#include <Core/Logger/Logger.hpp>
#include <Core/Utility/Memory.hpp>
#include <Core/Context/GameContext.hpp>

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



int main(int argc, char* argv[])
{
    ax::Game::initialize();
    ax::Game::start();

    for(int i = 0; i < 1000; i++)
    {
        ax::Entity& e = ax::Game::entities().create();
        e.addComponent<Position>();
    }

    auto& l = ax::Game::components().getList<Position>();
    ax::Game::logger().log((unsigned)l.size());
    ax::Game::logger().log((unsigned)l.memory().asBytes());

    ax::Game::logger().log(ax::Game::engine().config().getUnsigned("default", "version_major", 43));

    ax::Game::stop();
    ax::Game::terminate();

    return 0;
}