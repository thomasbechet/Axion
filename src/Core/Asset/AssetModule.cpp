#include <Core/Asset/AssetModule.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Builder/BuilderModule.hpp>

using namespace ax;

AssetModule::~AssetModule()
{
    dispose();
}

void AssetModule::dispose() noexcept
{
    for(auto& it : m_managers)
        it.get()->dispose();
}
void AssetModule::log() const noexcept
{
    Engine::logger().log("==================== ASSETS =====================", Severity::Info);

    for(auto& it : m_managers)
        it.get()->log();

    Engine::logger().log("=================================================", Severity::Info);
}

bool AssetModule::load(const std::string& type, const std::string& name, const Json& json) noexcept
{
    return Engine::builder().asset.get(type).load(name, json);
}
bool AssetModule::loadAsync(const std::string& type, const std::string& name, const Json& json) noexcept
{
    return Engine::builder().asset.get(type).loadAsync(name, json);
}
bool AssetModule::unload(const std::string& type, const std::string& name) noexcept
{
    return Engine::builder().asset.get(type).unload(name);
}
bool AssetModule::exists(const std::string& type, const std::string& name) const noexcept
{
    return Engine::builder().asset.get(type).exists(name);
}
bool AssetModule::wait(const std::string& type, const std::string& name) noexcept
{
    return Engine::builder().asset.get(type).wait(name);
}
void AssetModule::dispose(const std::string& type) noexcept
{
    Engine::builder().asset.get(type).dispose();
}
void AssetModule::log(const std::string& type) const noexcept
{
    Engine::builder().asset.get(type).log();
}