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
#include <Core/CoreSystems/Renderer.hpp>
#include <Core/World/Entity/ComponentIterator.hpp>
#include <Core/Logger/Logger.hpp>
#include <Core/Utility/Memory.hpp>
#include <Core/Context/GameContext.hpp>
#include <Core/System/System.hpp>
#include <Core/System/SystemManager.hpp>

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

class StaticMeshSystem : public ax::System
{
public:
    unsigned func(){return 5;}

    static std::string name(){return "StaticMeshSystem";}
};

int main(int argc, char* argv[])
{
    ax::Game::initialize();
    ax::Game::engine().start();
    ax::Game::terminate();

    //ax::Game::systems().add<StaticMeshSystem>();
    //ax::Game::logger().log(ax::Game::systems().get<StaticMeshSystem>().func());
    //ax::Game::stop();

    return 0;
}