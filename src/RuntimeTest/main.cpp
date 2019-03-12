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
#include <Core/Prefab/Component/DirectionalLightComponent.hpp>
#include <Core/Prefab/Component/Shape/UVSphereComponent.hpp>
#include <Core/Prefab/Component/Shape/RectangleComponent.hpp>
#include <Core/Prefab/Component/Shape/QuadComponent.hpp>
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
    static const std::string name;

    float x;
    float y;
    float z;
};

const std::string Position::name = "Position";

struct Staticsponza : public ax::Component
{
    void load(const ax::Entity& e) noexcept
    {
        position = &e.getComponent<Position>();       
    }
    void unload() noexcept 
    {
        
    }
    static std::string name(){return "Staticsponza";}

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

class StaticsponzaSystem : public ax::System
{
public:
    static const std::string name;

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

const std::string StaticsponzaSystem::name = "Staticsponza";

class MyGameMode : public ax::GameMode
{
public:
    void onStart() override
    {
        ax::Engine::assets().package.loadFromFile("mypackage", "../packages/package.json");
        ax::Engine::assets().log();

        ax::Engine::systems().add<ax::BasicWindowSystem>();
        ax::BasicSpectatorSystem& cameraSystem = ax::Engine::systems().add<ax::BasicSpectatorSystem>();
        ax::Engine::systems().add<ax::RenderModeSystem>();

        ax::Entity& camera0 = ax::Engine::world().entity.create();
        ax::TransformComponent& cameraTransform = camera0.addComponent<ax::TransformComponent>();
        ax::CameraComponent& cameraComponent0 = camera0.addComponent<ax::CameraComponent>(camera0);
        cameraComponent0.setFarPlane(100000000.0f);
        cameraComponent0.setFarPlane(100.0f);
        cameraComponent0.setNearPlane(0.01f);
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
            ax::Entity& camera1 = ax::Engine::world().entity.create();
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
            //ax::Engine::renderer().setViewportResolution(ax::Renderer::DefaultViewport, ax::Vector2u(512, 288));
            //ax::Engine::renderer().setViewportResolution(ax::Renderer::DefaultViewport, ax::Vector2u(3840, 2160));
        #endif

        //Plane
        ax::MaterialParameters wallMaterialParams;
        wallMaterialParams.normalTexture = "wall_normal2";
        ax::Engine::assets().material.loadFromMemory("wall_material", wallMaterialParams);

        ax::Entity& plane = ax::Engine::world().entity.create();
        plane.addComponent<ax::TransformComponent>();
        plane.addComponent<ax::QuadComponent>(plane, 500.0f, 500.0f, 100.0f).setMaterial("wall_material");

        CustomSystem& system = ax::Engine::systems().add<CustomSystem>();
        system.setSpawnTransform(&cameraTransform);
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