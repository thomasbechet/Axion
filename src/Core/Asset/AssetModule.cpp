#include <Core/Asset/AssetModule.hpp>

using namespace ax;

AssetModule::AssetModule() :
    package(loader),
    model(loader),
    material(loader),
    shader(loader),
    mesh(loader),
    texture(loader),
    scene(loader)
{

}
AssetModule::~AssetModule()
{
    dispose();
}

void AssetModule::dispose() noexcept
{
    package.dispose();
    model.dispose();
    material.dispose();
    shader.dispose();
    mesh.dispose();
    texture.dispose();
    scene.dispose();
}
void AssetModule::log() const noexcept
{
    Engine::logger().log("==================== ASSETS =====================", Severity::Info);

    package.log();
    model.log();
    material.log();
    shader.log();
    mesh.log();
    texture.log();
    scene.log();

    Engine::logger().log("=================================================", Severity::Info);
}