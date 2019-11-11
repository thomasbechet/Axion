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
#include <Core/Logger/LoggerModule.hpp>
#include <Core/Utility/Memory.hpp>
#include <Core/Context/ContextModule.hpp>
#include <Core/Scene/System/System.hpp>
#include <Core/Scene/System/SystemManager.ipp>
#include <Core/Input/InputModule.hpp>
#include <Core/Window/WindowModule.hpp>
#include <Core/Content/System/BasicWindowSystem.hpp>
#include <Core/Content/System/BasicSpectatorSystem.hpp>
#include <Core/Content/System/RenderModeSystem.hpp>
#include <Core/Content/Component/CameraComponent.hpp>
#include <Core/Content/Component/TransformComponent.hpp>
#include <Core/Content/Component/ModelComponent.hpp>
#include <Core/Content/Component/PointLightComponent.hpp>
#include <Core/Content/Component/DirectionalLightComponent.hpp>
#include <Core/Content/Component/Shape/UVSphereShapeComponent.hpp>
#include <Core/Content/Component/Shape/RectangleShapeComponent.hpp>
#include <Core/Content/Component/Shape/QuadShapeComponent.hpp>
#include <Core/Utility/Path.hpp>
#include <Core/Utility/IndexVector.hpp>
#include <Core/Asset/AssetModule.hpp>
#include <Core/Asset/AssetHolder.hpp>
#include <Core/Content/Asset/Package.hpp>
#include <RuntimeTest/CustomSystem.hpp>
#include <Core/Math/Transform2D.hpp>
#include <Core/Utility/Macro.hpp>
#include <Core/Builder/BuilderModule.hpp>
#include <Core/Utility/ChunkContainer.ipp>
#include <Core/Utility/Reference.ipp>

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
        //ax::Quaternionf quat(90.0, 90.0, 0.0);
        ax::Quaternionf quat("[90.0, 90.0, 0.0]"_json);
        std::cout << quat.json() << std::endl;

        std::cin.get();

        ax::Engine::scene().system.add<ax::BasicWindowSystem>();
        ax::Engine::scene().system.add<ax::RenderModeSystem>();

        ax::Engine::asset().load({
            {"name", "test_texture"},
            {"type", "texture"},
            {"source","$ENGINE_DIR/textures/wall_normal2.bmp"}
        }, true);

        //ax::Reference<ax::Texture> ref = ax::Engine::asset().get<ax::Texture>("test_texture");

        ax::Texture::Parameters textureParameters;
        textureParameters.source = "$ENGINE_DIR/textures/wall_normal2.bmp";
        ax::Engine::asset().load<ax::Texture>("mytexture", textureParameters);       

        ax::Engine::asset().loader.resetLoadState();

        ax::Package::Parameters packageParameters;
        packageParameters.source = "../packages/package.json";
        ax::Engine::asset().loadAsync<ax::Package>("mypackage", packageParameters);

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
        ax::Engine::asset().load<ax::Material>("wall_material", wallMaterialParams);

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

//ENGINE_INIT(MyGameMode)

int main(int argc, char* argv[])
{
    ax::Engine::initialize();
    ax::Engine::scene().gamemode.set<MyGameMode>();
    ax::Engine::context().run();
    ax::Engine::terminate();
    std::cout << "end reached" << std::endl;
    return 0;
}