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
#include <Core/Prefabs/Component/PointLightComponent.hpp>
#include <Core/Utility/Path.hpp>
#include <Core/Utility/IndexVector.hpp>
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
        ax::Engine::assets().package.create("mypackage", "../packages/package.xml");
        ax::Engine::assets().log();

        ax::Engine::systems().add<ax::BasicWindowSystem>();
        ax::BasicSpectatorSystem& cameraSystem = ax::Engine::systems().add<ax::BasicSpectatorSystem>();
        ax::Engine::systems().add<ax::RenderModeSystem>();

        ax::Entity& camera0 = ax::Engine::world().entities().create();
        camera0.addComponent<ax::TransformComponent>();
        ax::CameraComponent& cameraComponent0 = camera0.addComponent<ax::CameraComponent>(camera0);
        cameraComponent0.setFarPlane(300.0f);
        cameraComponent0.bindDefaultViewport();
        ax::BasicSpectatorComponent& spectatorComponent0 = camera0.addComponent<ax::BasicSpectatorComponent>(camera0);
        camera0.addComponent<ax::ModelComponent>(camera0).setModel("model_cube");
        cameraSystem.add(spectatorComponent0);

        //#define USE_CAMERA
        #if defined USE_CAMERA
            ax::Entity& camera1 = ax::Engine::world().entities().create();
            camera1.addComponent<ax::TransformComponent>();
            ax::CameraComponent& cameraComponent1 = camera1.addComponent<ax::CameraComponent>(camera1);
            cameraComponent1.setFarPlane(300.0f);
            ax::BasicSpectatorComponent& spectatorComponent1 = camera1.addComponent<ax::BasicSpectatorComponent>(camera1);
            camera1.addComponent<ax::ModelComponent>(camera1).setModel("model_cube");
            cameraSystem.add(spectatorComponent1);

            ax::Id viewport = ax::Engine::renderer().createViewport(ax::Vector2f(0.5f, 0.0f), ax::Vector2f(0.5f, 1.0f));
            cameraComponent1.bindViewport(viewport);

            ax::Engine::renderer().setViewportRectangle(ax::Renderer::DefaultViewport, ax::Vector2f(0.0f, 0.0f), ax::Vector2f(0.5f, 1.0f));
        #endif

        #define LOW_RESOLUTION
        #if defined LOW_RESOLUTION
            ax::Engine::renderer().setViewportResolution(ax::Renderer::DefaultViewport, ax::Vector2u(512, 288));
        #endif
        

        ax::Entity& mesh = ax::Engine::world().entities().create();
        ax::TransformComponent& transform1 = mesh.addComponent<ax::TransformComponent>();
        transform1.setScale(0.05f, 0.05f, 0.05f);
        transform1.setTranslation(0.0f, 0.0f, 0.0f);
        mesh.addComponent<ax::ModelComponent>(mesh).setModel("model_sponza");

        ax::Entity& cube = ax::Engine::world().entities().create();        
        ax::TransformComponent& transformCube = cube.addComponent<ax::TransformComponent>();
        transformCube.translate(ax::Vector3f(0, 4, 0));
        ax::ModelComponent& cubeModel = cube.addComponent<ax::ModelComponent>(cube);
        cubeModel.setModel("model_cube");

        //Light
        ax::Entity& light = ax::Engine::world().entities().create();
        light.addComponent<ax::TransformComponent>();
        light.addComponent<ax::PointLightComponent>(light);

        //ax::Engine::systems().add<CustomSystem>().setTransform(&transform1);
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