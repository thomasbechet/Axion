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
#include <Core/Prefab/System/BasicWindowSystem.hpp>
#include <Core/Prefab/System/BasicSpectatorSystem.hpp>
#include <Core/Prefab/System/RenderModeSystem.hpp>
#include <Core/Prefab/Component/CameraComponent.hpp>
#include <Core/Prefab/Component/TransformComponent.hpp>
#include <Core/Prefab/Component/ModelComponent.hpp>
#include <Core/Prefab/Component/PointLightComponent.hpp>
#include <Core/Prefab/Component/Shape/UVSphereComponent.hpp>
#include <Core/Prefab/Component/Shape/RectangleComponent.hpp>
#include <Core/Utility/Path.hpp>
#include <Core/Utility/IndexVector.hpp>
#include <Core/Asset/AssetManager.hpp>
#include <Core/Asset/Texture.hpp>
#include <Core/Asset/AssetHolder.hpp>
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
        ax::MaterialParameters materialParameters;
        materialParameters.diffuseTexture = "texture_brick_diffuse";
        materialParameters.normalTexture = "texture_brick_normal";
        ax::AssetReference<ax::Material> m = ax::Engine::assets().material.create("mymaterial", materialParameters);


        ax::Engine::assets().log();

        ax::Engine::systems().add<ax::BasicWindowSystem>();
        ax::BasicSpectatorSystem& cameraSystem = ax::Engine::systems().add<ax::BasicSpectatorSystem>();
        ax::Engine::systems().add<ax::RenderModeSystem>();

        ax::Entity& camera0 = ax::Engine::world().entities().create();
        ax::TransformComponent& cameraTransform = camera0.addComponent<ax::TransformComponent>();
        ax::CameraComponent& cameraComponent0 = camera0.addComponent<ax::CameraComponent>(camera0);
        cameraComponent0.setFarPlane(300.0f);
        cameraComponent0.bindDefaultViewport();
        ax::BasicSpectatorComponent& spectatorComponent0 = camera0.addComponent<ax::BasicSpectatorComponent>(camera0);
        cameraSystem.add(spectatorComponent0);

        //#define USE_SNIPER
        #if defined USE_SNIPER
            ax::Entity& sniper = ax::Engine::world().entities().create();
            ax::TransformComponent& strans = sniper.addComponent<ax::TransformComponent>();
            strans.rotate(ax::radians(-90.0f), ax::Vector3f(0.0f, 1.0f, 0.0f));
            strans.setScale(0.3f, 0.3f, 0.3f);
            strans.setTranslation(-0.3f, -0.2f, 0.2f);
            strans.attachTo(camera0);
            sniper.addComponent<ax::ModelComponent>(sniper).setModel("model_sniper");
        #endif
        

        //#define USE_CAMERA
        #if defined USE_CAMERA
            ax::Entity& camera1 = ax::Engine::world().entities().create();
            camera1.addComponent<ax::TransformComponent>();
            ax::CameraComponent& cameraComponent1 = camera1.addComponent<ax::CameraComponent>(camera1);
            cameraComponent1.setFarPlane(300.0f);
            ax::BasicSpectatorComponent& spectatorComponent1 = camera1.addComponent<ax::BasicSpectatorComponent>(camera1);
            cameraSystem.add(spectatorComponent1);

            ax::Id viewport = ax::Engine::renderer().createViewport(ax::Vector2f(0.5f, 0.0f), ax::Vector2f(0.5f, 1.0f));
            cameraComponent1.bindViewport(viewport);

            ax::Engine::renderer().setViewportRectangle(ax::Renderer::DefaultViewport, ax::Vector2f(0.0f, 0.0f), ax::Vector2f(0.5f, 1.0f));
        #endif

        #define LOW_RESOLUTION
        #if defined LOW_RESOLUTION
            ax::Engine::renderer().setViewportResolution(ax::Renderer::DefaultViewport, ax::Vector2u(512, 288));
        #endif
        
        #define USE_SPONZA
        #if defined USE_SPONZA
            ax::Entity& mesh = ax::Engine::world().entities().create();
            ax::TransformComponent& transform1 = mesh.addComponent<ax::TransformComponent>();
            transform1.setScale(0.05f, 0.05f, 0.05f);
            transform1.setTranslation(0.0f, 0.0f, 0.0f);
            mesh.addComponent<ax::ModelComponent>(mesh).setModel("model_sponza");
        #endif
        

        ax::Entity& e1 = ax::Engine::world().entities().create();        
        ax::TransformComponent& transformCube = e1.addComponent<ax::TransformComponent>();
        transformCube.translate(ax::Vector3f(0, 5, 0));
        //ax::ModelComponent& cubeModel = cube.addComponent<ax::ModelComponent>(e1);
        //cubeModel.setModel("model_cube");
        //cubeModel.setMaterial("mymaterial");
        ax::UVSphereComponent& sphere = e1.addComponent<ax::UVSphereComponent>(e1);
        sphere.setMaterial("mymaterial");
        sphere.setRadius(10.0f);
        sphere.setCoordinateFactor(10.0f);
        sphere.setSliceCount(100);
        sphere.setStackCount(100);
        sphere.generate();


        ax::Entity& e2 = ax::Engine::world().entities().create();        
        ax::TransformComponent& e2Trans = e2.addComponent<ax::TransformComponent>();
        e2Trans.translate(ax::Vector3f(0, 30, 0));
        ax::RectangleComponent& cubeComponent = e2.addComponent<ax::RectangleComponent>(e2);
        cubeComponent.setMaterial("mymaterial");
        cubeComponent.setCoordinateFactor(10.0f);
        cubeComponent.setMaxX(10.0f);
        cubeComponent.setMaxY(10.0f);
        cubeComponent.setMaxZ(10.0f);
        cubeComponent.generate();

        //Light
        ax::Entity& light = ax::Engine::world().entities().create();
        light.addComponent<ax::TransformComponent>().setTranslation(10.0f, 0.0f, 0.0f);
        light.addComponent<ax::PointLightComponent>(light);

        ax::Engine::systems().add<CustomSystem>().setTransform(&cameraTransform);
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