#include <iostream>

#include <Core/Math/Vector.hpp>
#include <Core/Math/Matrix.hpp>
#include <Core/Math/Math.hpp>
#include <Core/Math/Transform.hpp>
#include <Core/Utility/ThreadPool.hpp>
#include <Core/Utility/Timer.hpp>
#include <Core/World/Entity/Entity.hpp>
#include <Core/World/Entity/EntityManager.hpp>
#include <Core/Context/Engine.hpp>
#include <Core/Renderer/Renderer.hpp>
#include <Core/World/Component/ComponentIterator.hpp>
#include <Core/Logger/Logger.hpp>
#include <Core/Utility/Memory.hpp>
#include <Core/Context/EngineContext.hpp>
#include <Core/System/System.hpp>
#include <Core/System/SystemManager.hpp>
#include <Core/Input/Input.hpp>
#include <Core/Window/Window.hpp>
#include <Core/Prefabs/System/BasicWindowSystem.hpp>
#include <Core/Prefabs/System/BasicSpectatorSystem.hpp>
#include <Core/Prefabs/System/RenderModeSystem.hpp>
#include <Core/Prefabs/Component/CameraComponent.hpp>
#include <Core/Prefabs/Component/TransformComponent.hpp>
#include <Core/Prefabs/Component/ModelComponent.hpp>
#include <Core/Utility/Path.hpp>
#include <Core/Assets/AssetManager.hpp>
#include <Core/Assets/Texture.hpp>
#include <Core/Assets/AssetHolder.hpp>
#include <RuntimeTest/CustomSystem.hpp>

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

    ax::Id id;
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

    void onInitialize() override
    {

    }
    void onTerminate() override
    {
        
    }

    void onStart() override
    {
        m_timer.start();
    }
    void onUpdate() override
    {
        
    }
    void onFixedUpdate() override
    {
        
    }   
    void onStop() override
    {
        
    }

    ax::Timer m_timer;
};

class MyGameMode : public ax::GameMode
{
public:
    void onStart() override
    {
        ax::Engine::assets().package.load("../packages/package.xml");
        ax::Engine::assets().log();

        ax::Engine::systems().add<ax::BasicWindowSystem>();
        ax::Engine::systems().add<ax::BasicSpectatorSystem>();
        ax::Engine::systems().add<ax::RenderModeSystem>();


        ax::Entity& camera = ax::Engine::world().entities().create();
        camera.addComponent<ax::TransformComponent>();
        camera.addComponent<ax::CameraComponent>(camera).setFarPlane(300.0f);
        camera.addComponent<ax::BasicSpectatorComponent>(camera);


        ax::Entity& mesh = ax::Engine::world().entities().create();
        ax::TransformComponent& transform1 = mesh.addComponent<ax::TransformComponent>();
        //transform1.setScale(0.05f, 0.05f, 0.05f);
        transform1.setScale(1.0f, 1.0f, 1.0f);
        transform1.setTranslation(0.0f, 0.0f, 0.0f);
        //mesh.addComponent<ax::ModelComponent>(mesh).setModel("model_sponza");

        ax::MaterialParameters params;
        params.diffuseUniform = ax::Color(0.233f, 0.531f, 0.13f);
        ax::Engine::assets().material.load("material_test", params);

        material->getDiffuseTexture();
        material->setDiffuseTexture();

        const int size = 10;
        for(int x = -size / 2; x < size / 2; x += 1)
            for(int y = -size / 2; y < size / 2; y += 1)
                for(int z = -size / 2; z < size / 2; z += 1)
            {
                ax::Entity& cube = ax::Engine::world().entities().create();        
                ax::TransformComponent& transformCube = cube.addComponent<ax::TransformComponent>();
                transformCube.translate(ax::Vector3f(x * 4, z * 4, y * 4));
                transformCube.rotate(x, ax::Vector3f(1.0f, 0.0f, 0.0f));
                transformCube.attachTo(mesh);
                ax::ModelComponent& cubeModel = cube.addComponent<ax::ModelComponent>(cube);
                cubeModel.setModel("model_cube");
                cubeModel.setMaterial("material_test", 0);
            }

        ax::Engine::systems().add<CustomSystem>().setTransform(&transform1);
    }
    void onStop() override
    {
        ax::Engine::systems().remove<ax::BasicWindowSystem>();
        ax::Engine::systems().remove<ax::BasicSpectatorSystem>();
        ax::Engine::systems().remove<ax::RenderModeSystem>();
    }
};

int main(int argc, char* argv[])
{
    ax::Engine::initialize();
    ax::Engine::world().setGameMode<MyGameMode>();
    ax::Engine::context().run();
    ax::Engine::terminate();

    std::cout << "end reached" << std::endl;

    return 0;
}