#include <Core/Scene/SceneModule.hpp>

#include <Core/Asset/AssetModule.ipp>

using namespace ax;

void SceneModule::open(const std::string& scene) noexcept
{
    open(Engine::asset().get<Scene>(scene));
}
void SceneModule::open(Reference<Scene> scene) noexcept
{
    
}