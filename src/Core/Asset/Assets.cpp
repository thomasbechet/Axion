#include <Core/Asset/Assets.hpp>

using namespace ax;

Assets::Assets() :
    package(loader),
    model(loader),
    material(loader),
    shader(loader),
    mesh(loader),
    texture(loader)
{

}
Assets::~Assets()
{
    dispose();
}

void Assets::dispose() noexcept
{
    package.dispose();
    model.dispose();
    material.dispose();
    shader.dispose();
    mesh.dispose();
    texture.dispose();
}
void Assets::log() const noexcept
{
    Engine::logger().log("==================== ASSETS =====================", Logger::Info);

    package.log();
    model.log();
    material.log();
    shader.log();
    mesh.log();
    texture.log();

    Engine::logger().log("=================================================", Logger::Info);
} 