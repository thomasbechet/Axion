#include <Core/Assets/AssetManager.hpp>

#include <Core/Context/Game.hpp>
#include <Core/Logger/Logger.hpp>

using namespace ax;

AssetManager::~AssetManager()
{
    dispose();
}

void AssetManager::dispose() noexcept
{
    package.dispose();
    model.dispose();
    material.dispose();
    shader.dispose();
    mesh.dispose();
    texture.dispose();
}
void AssetManager::log() const noexcept
{
    package.log();
    model.log();
    material.log();
    shader.log();
    mesh.log();
    texture.log();
}