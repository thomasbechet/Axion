#include <iostream>
#include <iomanip>

#include <Core/Math/Vector.hpp>
#include <Core/Math/Matrix.hpp>
#include <Core/Math/Math.hpp>
#include <Core/Content/Component/TransformComponent.hpp>
#include <Core/Utility/ThreadPool.hpp>
#include <Core/Utility/Timer.hpp>
#include <Core/Scene/Entity/Entity.hpp>
#include <Core/Scene/Entity/EntityManager.hpp>
#include <Core/Scene/GameMode/GameModeManager.ipp>
#include <Core/Engine/Engine.hpp>
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
#include <Core/Content/Asset/PackageAsset.hpp>
#include <RuntimeTest/CustomSystem.hpp>
#include <Core/Math/Transform2D.hpp>
#include <Core/Utility/Macro.hpp>
#include <Core/Builder/BuilderModule.hpp>
#include <Core/Utility/ChunkContainer.ipp>
#include <Core/Utility/Reference.ipp>

class MyGameMode : public ax::GameMode
{
public:
    void onStart() override
    {
        ax::Engine::scene().system.add<ax::BasicWindowSystem>();
        ax::Engine::scene().system.add<ax::RenderModeSystem>();

        ax::Engine::builder().component.record<RotationComponent>();

        ax::Engine::asset().load({
            {"name", "test_texture"},
            {"type", "texture"},
            {"source","$ENGINE_DIR/textures/wall_normal2.bmp"}
        }, true);

        //ax::Reference<ax::Texture> ref = ax::Engine::asset().get<ax::Texture>("test_texture");

        ax::TextureAsset::Parameters textureParameters;
        textureParameters.source = "$ENGINE_DIR/textures/wall_normal2.bmp";
        ax::Engine::asset().load<ax::TextureAsset>("mytexture", textureParameters);       

        ax::Engine::asset().loader.resetLoadState();

        ax::PackageAsset::Parameters packageParameters;
        packageParameters.source = "../packages/package.json";
        ax::Engine::asset().loadAsync<ax::PackageAsset>("main_package", packageParameters);

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

        ax::Engine::scene().system.add<RotationSystem>();

        ax::Timer timer;
        timer.start();

        ax::

        ax::Engine::scene().open("balls_scene");

        std::cout << timer.getElapsedTime().asMilliseconds() << std::endl;

        //ax::Engine::asset().log();
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