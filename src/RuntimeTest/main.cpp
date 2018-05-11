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

struct Position : public ax::Component
{
    void load(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) noexcept
    {
        x = _x;
        y = _y;
        z = _z;
    }
    void unload(){}
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
    void unload() noexcept {}
    static std::string name() {return "StaticMesh";}

    ax::Renderer::Id id;
    Position* position;
};



int main(int argc, char* argv[])
{
    ax::Game::initialize();

    /*ax::Entity& e = ax::Game::entities().createEntity();
    e.addComponent<Position>(1.0f, 1.0f, 1.0f);

    auto& cmp = e.getComponent<StaticMesh>();

    auto& list = ax::Game::components().getComponentList<Position>();
    ax::ComponentIterator<Position> it(list, 0, list.length());
    while(it.next())
    {
        ax::Game::logger().log(std::to_string(it->x), ax::Logger::NONE);
    }*/

    ax::Entity& e = ax::Game::entities().createEntity();
    e.addComponent<Position>();
    e.removeComponent<StaticMesh>();

    ax::Game::terminate();

    return 0;
}