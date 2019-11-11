#include <Core/Asset/AssetModule.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Builder/BuilderModule.hpp>
#include <Core/Asset/JsonAttributes.hpp>

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
 
BasicReference AssetModule::get(const std::string& type, const std::string& name) noexcept
{
    try
    {
        return Engine::builder().asset.get(type).get(name);
    }
    catch(const std::out_of_range& e)
    {
        Engine::interrupt("Failed to access asset because '" + type + "' asset type doesn't exists");
    }
}
bool AssetModule::load(const Json& json, bool validate) noexcept
{
    try
    {
        std::string type = json.find(JsonAttributes::type)->get<std::string>();
        return Engine::builder().asset.get(type).load(json, validate);
    }
    catch(const std::out_of_range& e)
    {
        Engine::logger().log("Failed to load asset because '" + std::string(e.what()) + "' asset type doesn't exists", Severity::Warning);
        return false;
    }
    catch(const std::exception& e)
    {
        Engine::logger().log("Failed to load asset because it doesn't have '" + JsonAttributes::type + "' attribute", Severity::Warning);
        return false;
    }   
}
bool AssetModule::loadAsync(const Json& json) noexcept
{
    try
    {
        std::string type = json.find(JsonAttributes::type)->get<std::string>();
        return Engine::builder().asset.get(type).loadAsync(json);
    }
    catch(const std::out_of_range& e)
    {
        Engine::logger().log("Failed to load async asset because '" + std::string(e.what()) + "' asset type doesn't exists", Severity::Warning);
        return false;
    }
    catch(const std::exception& e)
    {
        Engine::logger().log("Failed to load async asset because it doesn't have '" + JsonAttributes::type + "' attribute", Severity::Warning);
        return false;
    }
}
bool AssetModule::unload(const std::string& type, const std::string& name) noexcept
{
    try
    {
        return Engine::builder().asset.get(type).unload(name);
    }
    catch(const std::out_of_range& e)
    {
        Engine::logger().log("Failed to unload asset because '" + std::string(e.what()) + "' asset type doesn't exists", Severity::Warning);
        return false;
    }
}
bool AssetModule::exists(const std::string& type, const std::string& name) const noexcept
{
    try
    {
        return Engine::builder().asset.get(type).exists(name);
    }
    catch(const std::out_of_range& e)
    {
        Engine::logger().log("Failed to test asset existence because '" + std::string(e.what()) + "' asset type doesn't exists", Severity::Warning);
        return false;
    }
}
bool AssetModule::wait(const std::string& type, const std::string& name) noexcept
{
    try
    {
        return Engine::builder().asset.get(type).wait(name);
    }
    catch(const std::out_of_range& e)
    {
        Engine::logger().log("Failed to wait asset because '" + std::string(e.what()) + "' asset type doesn't exists", Severity::Warning);
        return false;
    }
}
void AssetModule::dispose(const std::string& type) noexcept
{
    try
    {
        Engine::builder().asset.get(type).dispose();
    }
    catch(const std::out_of_range& e)
    {
        Engine::logger().log("Failed to dispose asset because '" + std::string(e.what()) + "' asset type doesn't exists", Severity::Warning);
    }
}
void AssetModule::log(const std::string& type) const noexcept
{
    try
    {
        Engine::builder().asset.get(type).log();
    }
    catch(const std::out_of_range& e)
    {
        Engine::logger().log("Failed to log asset because '" + std::string(e.what()) + "' asset type doesn't exists", Severity::Warning);
    }
}