#include <iostream>
#include <iomanip>

#include <Core/Math/Vector.hpp>
#include <Core/Math/Matrix.hpp>
#include <Core/Math/Math.hpp>
#include <Core/Math/Transform.hpp>
#include <Core/Utility/ThreadPool.hpp>
#include <Core/Utility/Timer.hpp>
#include <Core/Scene/Entity/Entity.hpp>
#include <Core/Scene/Entity/EntityManager.hpp>
#include <Core/Scene/GameMode/GameModeManager.ipp>
#include <Core/Context/Engine.hpp>
#include <Core/Renderer/RendererModule.hpp>
#include <Core/Scene/Component/ComponentIterator.hpp>
#include <Core/Logger/LoggerModule.hpp>
#include <Core/Utility/Memory.hpp>
#include <Core/Context/ContextModule.hpp>
#include <Core/Scene/System/System.hpp>
#include <Core/Scene/System/SystemManager.ipp>
#include <Core/Input/InputModule.hpp>
#include <Core/Window/WindowModule.hpp>
#include <Core/Prefab/System/BasicWindowSystem.hpp>
#include <Core/Prefab/System/BasicSpectatorSystem.hpp>
#include <Core/Prefab/System/RenderModeSystem.hpp>
#include <Core/Prefab/Component/CameraComponent.hpp>
#include <Core/Prefab/Component/TransformComponent.hpp>
#include <Core/Prefab/Component/ModelComponent.hpp>
#include <Core/Prefab/Component/PointLightComponent.hpp>
#include <Core/Prefab/Component/DirectionalLightComponent.hpp>
#include <Core/Prefab/Component/Shape/UVSphereShapeComponent.hpp>
#include <Core/Prefab/Component/Shape/RectangleShapeComponent.hpp>
#include <Core/Prefab/Component/Shape/QuadShapeComponent.hpp>
#include <Core/Utility/Path.hpp>
#include <Core/Utility/IndexVector.hpp>
#include <Core/Asset/AssetModule.hpp>
#include <Core/Asset/AssetHolder.hpp>
#include <RuntimeTest/CustomSystem.hpp>
#include <Core/Math/Transform2D.hpp>
#include <Core/Utility/Macro.hpp>
#include <Core/Builder/BuilderModule.hpp>
#include <Core/Utility/ChunkContainer.ipp>

struct Position : public ax::Component
{
    COMPONENT_IDENTIFIER("Position")
    COMPONENT_REQUIREMENT(ax::TransformComponent, ax::ModelComponent)

    Position(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

    void load(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) noexcept
    {
        x = _x;
        y = _y;
        z = _z;
    }
    void unload()
    {
        
    }
    static const std::string type;

    float x;
    float y;
    float z;
};

struct Staticsponza : public ax::Component
{
    COMPONENT_IDENTIFIER("StaticSponza")

    void load(const ax::Entity& e) noexcept
    {
        position = &e.getComponent<Position>();       
    }
    void unload() noexcept 
    {
        
    }

    ax::Id id;
    Position* position;
};

class StaticsponzaSystem : public ax::System
{
public:
    SYSTEM_IDENTIFIER("StaticSponza")

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
        ax::ChunkContainer<Position, 1000> chunks;
        for(int i = 0; i < 1000000; i++) {
            chunks.add(1 * i, 2, 3);
        }
        chunks.remove(55555);
        std::cout << chunks.add(1, 2, 3) << std::endl;
        chunks.remove(1000002);
        std::cout << chunks.size() << std::endl;

        std::cin.get();

        ax::Engine::scene().system.add<ax::BasicWindowSystem>();
        ax::Engine::scene().system.add<ax::RenderModeSystem>();

        ax::Texture::Parameters textureParameters;
        textureParameters.source = "$ENGINE_DIR/textures/wall_normal2.bmp";
        ax::Engine::asset().texture.load("mytexture", textureParameters);       

        ax::Engine::asset().loader.resetLoadState();

        ax::Package::Parameters packageParameters;
        packageParameters.source = "../packages/package.json";
        packageParameters.asyncLoading = true;
        ax::Engine::asset().package.loadAsync("mypackage", packageParameters);

        ax::AssetLoader::LoadState loadState;
        std::string lastName;
        do
        {
            loadState = ax::Engine::asset().loader.getLoadState();
            if(lastName != loadState.lastAsset.name)
            {
                ax::Engine::logger().log(loadState.str());
                lastName = loadState.lastAsset.name;
            }
        }
        while(loadState.isLoading);
        ax::Engine::asset().loader.waitAll();

        
        ax::BasicSpectatorSystem& cameraSystem = ax::Engine::scene().system.add<ax::BasicSpectatorSystem>();
        

        //ax::Entity& test = ax::Engine::world().entity.create("test");
        //ax::Entity& test = ax::Engine::world().scene.entity.create("test");


        ax::Entity& camera0 = ax::Engine::scene().entity.create();
        ax::TransformComponent& cameraTransform = camera0.addComponent<ax::TransformComponent>();
        ax::CameraComponent& cameraComponent0 = camera0.addComponent<ax::CameraComponent>();
        cameraComponent0.setFarPlane(100000000.0f);
        cameraComponent0.setFarPlane(100.0f);
        cameraComponent0.setNearPlane(0.01f);
        cameraComponent0.bindDefaultViewport();
        ax::BasicSpectatorComponent& spectatorComponent0 = camera0.addComponent<ax::BasicSpectatorComponent>();
        cameraSystem.add(spectatorComponent0);

        //#define USE_SNIPER
        #if defined USE_SNIPER
            ax::Entity& sniper = ax::Engine::scene().entities().create();
            ax::TransformComponent& strans = sniper.add<ax::TransformComponent>();
            strans.rotate(ax::radians(-90.0f), ax::Vector3f(0.0f, 1.0f, 0.0f));
            strans.setScale(0.3f, 0.3f, 0.3f);
            strans.setTranslation(-0.3f, -0.2f, 0.2f);
            strans.attachTo(camera0);
            sniper.add<ax::ModelComponent>().setModel("model_sniper");
        #endif
        

        //#define USE_CAMERA
        #if defined USE_CAMERA
            ax::Entity& camera1 = ax::Engine::scene().entity.create();
            camera1.addComponent<ax::TransformComponent>();
            ax::CameraComponent& cameraComponent1 = camera1.addComponent<ax::CameraComponent>();
            cameraComponent1.setFarPlane(300.0f);
            ax::BasicSpectatorComponent& spectatorComponent1 = camera1.addComponent<ax::BasicSpectatorComponent>();
            cameraSystem.add(spectatorComponent1);

            ax::Id viewport = ax::Engine::renderer().createViewport(ax::Vector2f(0.5f, 0.0f), ax::Vector2f(0.5f, 1.0f));
            cameraComponent1.bindViewport(viewport);

            ax::Engine::renderer().setViewportRectangle(ax::Renderer::DefaultViewport, ax::Vector2f(0.0f, 0.0f), ax::Vector2f(0.5f, 1.0f));
        #endif

        #define LOW_RESOLUTION
        #if defined LOW_RESOLUTION
            //ax::Engine::renderer().getDefaultViewport()->setResolution(ax::Vector2u(512, 288));
            //ax::Engine::renderer().setViewportResolution(ax::Renderer::DefaultViewport, ax::Vector2u(64, 36));
            //ax::Engine::renderer().setViewportResolution(ax::Renderer::DefaultViewport, ax::Vector2u(3840, 2160));
        #endif

        //Plane
        ax::Material::Parameters wallMaterialParams;
        wallMaterialParams.normalTexture = "wall_normal2";
        ax::Engine::asset().material.load("wall_material", wallMaterialParams);

        ax::Entity& plane = ax::Engine::scene().entity.create();
        plane.addComponent<ax::TransformComponent>();
        plane.addComponent<ax::QuadShapeComponent>(500.0f, 500.0f, 100.0f).setMaterial("wall_material");

        //Sponza
        ax::Entity& sponza = ax::Engine::scene().entity.create();
        sponza.addComponent<ax::TransformComponent>().setScale(0.05f, 0.05f, 0.05f);
        sponza.addComponent<ax::ModelComponent>().setModel("model_sponza");
        //Directional light
        ax::Entity& dlight = ax::Engine::scene().entity.create();        
        dlight.addComponent<ax::TransformComponent>().rotate(45.0f, ax::Vector3f(1.0f, 0.0f, 0.0f));
        //dlight.addComponent<ax::DirectionalLightComponent>(dlight);
        //ax::Engine::renderer().getDefaultViewport()->setResolution(ax::Vector2u(1366, 768));
        //ax::Engine::renderer().getDefaultViewport()->setResolution(ax::Vector2u(1600, 900));

        CustomSystem& system = ax::Engine::scene().system.add<CustomSystem>();
        system.setSpawnTransform(&cameraTransform);

        ax::Engine::asset().log();
    }
    void onStop() override
    {
        ax::Engine::scene().system.remove<ax::BasicWindowSystem>();
        ax::Engine::scene().system.remove<ax::BasicSpectatorSystem>();
        ax::Engine::scene().system.remove<ax::RenderModeSystem>();
    }
};

ENGINE_INIT(MyGameMode)