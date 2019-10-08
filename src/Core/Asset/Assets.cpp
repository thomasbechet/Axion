#include <Core/Asset/Assets.hpp>

#include <sstream>
#include <iomanip>

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
    std::stringstream ss;
    ss << std::setfill('#') << std::setw(30) << " ASSETS LOG ";
    //ss << "##############" << std::setw(12) << " ASSETS LOG " << std::setw(0) << "##############";
    //Engine::logger().log("############## ASSETS LOG ###############", Logger::Info);
    Engine::logger().log(ss.str(), Logger::Info);

    package.log();
    model.log();
    material.log();
    shader.log();
    mesh.log();
    texture.log();

    Engine::logger().log("#########################################", Logger::Info);
}
unsigned Assets::getTotalPending() noexcept
{
    return m_assetLoader.getTotalPending();
}
Asset::Information Assets::getCurrentAssetInformation() noexcept
{
    return m_assetLoader.getCurrentAssetInformation();
}