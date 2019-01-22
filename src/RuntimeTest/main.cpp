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
    static std::string name(){return "Position";};

    float x;
    float y;
    float z;
};

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
    static std::string name(){return "StaticsponzaSystem";}

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
        //materialParameters.diffuseTexture = "texture_brick_diffuse";
        //materialParameters.normalTexture = "texture_brick_normal";
		materialParameters.diffuseTexture = "texture_earth";
        ax::AssetReference<ax::Material> m = ax::Engine::assets().material.create("mymaterial", materialParameters);


        ax::Engine::assets().log();

        ax::Engine::systems().add<ax::BasicWindowSystem>();
        ax::BasicSpectatorSystem& cameraSystem = ax::Engine::systems().add<ax::BasicSpectatorSystem>();
        ax::Engine::systems().add<ax::RenderModeSystem>();

        ax::Entity& camera0 = ax::Engine::world().entities().create();
        ax::TransformComponent& cameraTransform = camera0.addComponent<ax::TransformComponent>();
        ax::CameraComponent& cameraComponent0 = camera0.addComponent<ax::CameraComponent>(camera0);
        cameraComponent0.setFarPlane(100000000.0f);
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

        //#define LOW_RESOLUTION
        #if defined LOW_RESOLUTION
            ax::Engine::renderer().setViewportResolution(ax::Renderer::DefaultViewport, ax::Vector2u(512, 288));
        #endif
        
        #define USE_SPONZA
        #if defined USE_SPONZA
            ax::Entity& sponza = ax::Engine::world().entities().create();
            ax::TransformComponent& sponzaTransform = sponza.addComponent<ax::TransformComponent>();
            sponzaTransform.setScale(0.05f, 0.05f, 0.05f);
            sponzaTransform.setTranslation(0.0f, 2.0f, 0.0f);
            sponza.addComponent<ax::ModelComponent>(sponza).setModel("model_sponza");
        #endif
        

        ax::Entity& rotator = ax::Engine::world().entities().create();   
        ax::TransformComponent& rotatorTransform = rotator.addComponent<ax::TransformComponent>();

        ax::Entity& sphere = ax::Engine::world().entities().create();        
        ax::TransformComponent& sphereTransform = sphere.addComponent<ax::TransformComponent>();
        sphereTransform.translate(ax::Vector3f(0, 3000000000.0f, 0));
        //sphereTransform.translate(ax::Vector3f(0, 3844000.0f, 0));
        ax::UVSphereComponent& sphereComponent = sphere.addComponent<ax::UVSphereComponent>(sphere);
        sphereComponent.setMaterial("mymaterial");
        sphereComponent.setRadius(1737000.0f);
        sphereComponent.setRadius(700000000.0f);
        sphereComponent.setCoordinateFactor(1.0f);
        sphereComponent.setSliceCount(100);
        sphereComponent.setStackCount(100);
        sphereComponent.generate();

        sphereTransform.attachTo(rotator);


        ax::Entity& rectangle = ax::Engine::world().entities().create();        
        ax::TransformComponent& rectangleTransform = rectangle.addComponent<ax::TransformComponent>();
        rectangleTransform.translate(ax::Vector3f(0, 0, 3));
        ax::RectangleComponent& rectangleComponent = rectangle.addComponent<ax::RectangleComponent>(rectangle);
        rectangleComponent.setMaterial("mymaterial");
        rectangleComponent.setCoordinateFactor(1.0f);
        rectangleComponent.setMaxX(1.0f);
        rectangleComponent.setMaxY(1.0f);
        rectangleComponent.setMaxZ(1.0f);
        rectangleComponent.generate();

        //Lights
        ax::Entity& pointLight = ax::Engine::world().entities().create();
        ax::TransformComponent& lightTransform = pointLight.addComponent<ax::TransformComponent>();
        pointLight.addComponent<ax::PointLightComponent>(pointLight);
        pointLight.addComponent<ax::UVSphereComponent>(pointLight, 0.1f);

        ax::Entity& directionalLight = ax::Engine::world().entities().create();
        directionalLight.addComponent<ax::TransformComponent>();
        directionalLight.addComponent<ax::DirectionalLightComponent>(directionalLight);

        //Plane
        ax::Entity& plane = ax::Engine::world().entities().create();
        plane.addComponent<ax::TransformComponent>();
        plane.addComponent<ax::QuadComponent>(plane, 2000.0f, 2000.0f);

        CustomSystem& system = ax::Engine::systems().add<CustomSystem>();
        system.setTransform(&rotatorTransform);
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