#include <Core/Asset/Assets.hpp>

using namespace ax;

Assets::Assets() :
    texture(m_assetLoader),
    mesh(m_assetLoader),
    shader(m_assetLoader),
    material(m_assetLoader),
    model(m_assetLoader),
    package(m_assetLoader)
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
AssetLoader::State Assets::getLoaderState() noexcept
{
    return m_assetLoader.getState();
}   