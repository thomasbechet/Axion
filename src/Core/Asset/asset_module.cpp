#include <core/asset/asset_module.hpp>

#include <core/engine/engine.hpp>
#include <core/builder/builder_module.hpp>
#include <core/asset/json_attributes.hpp>

using namespace ax;
using namespace ax::detail;

asset_module::~asset_module()
{
    dispose();
}

void asset_module::dispose() noexcept
{
    for(auto& it : m_managers)
        it.get()->dispose();
}
void asset_module::log() const noexcept
{
    engine::logger().log("==================== ASSETS =====================", severity::info);

    for(auto& it : m_managers)
        it.get()->log();

    engine::logger().log("=================================================", severity::info);
}
 
basic_reference asset_module::get(const std::string& type, const std::string& name) noexcept
{
    try
    {
        return engine::builder().asset.get(type).get(name);
    }
    catch(const std::out_of_range& e)
    {
        engine::interrupt("Failed to access asset because '" + type + "' asset type doesn't exists");
    }
}
bool asset_module::load(const json& json, bool validate) noexcept
{
    try
    {
        std::string type = json.find(json_attributes::type)->get<std::string>();
        return engine::builder().asset.get(type).load(json, validate);
    }
    catch(const std::out_of_range& e)
    {
        engine::logger().log("Failed to load asset because '" + std::string(e.what()) + "' asset type doesn't exists", severity::warning);
        return false;
    }
    catch(const std::exception& e)
    {
        engine::logger().log("Failed to load asset because it doesn't have '" + json_attributes::type + "' attribute", severity::warning);
        return false;
    }   
}
bool asset_module::load_async(const json& json) noexcept
{
    try
    {
        std::string type = json.find(json_attributes::type)->get<std::string>();
        return engine::builder().asset.get(type).load_async(json);
    }
    catch(const std::out_of_range& e)
    {
        engine::logger().log("Failed to load async asset because '" + std::string(e.what()) + "' asset type doesn't exists", severity::warning);
        return false;
    }
    catch(const std::exception& e)
    {
        engine::logger().log("Failed to load async asset because it doesn't have '" + json_attributes::type + "' attribute", severity::warning);
        return false;
    }
}
bool asset_module::unload(const std::string& type, const std::string& name) noexcept
{
    try
    {
        return engine::builder().asset.get(type).unload(name);
    }
    catch(const std::out_of_range& e)
    {
        engine::logger().log("Failed to unload asset because '" + std::string(e.what()) + "' asset type doesn't exists", severity::warning);
        return false;
    }
}
bool asset_module::exists(const std::string& type, const std::string& name) const noexcept
{
    try
    {
        return engine::builder().asset.get(type).exists(name);
    }
    catch(const std::out_of_range& e)
    {
        engine::logger().log("Failed to test asset existence because '" + std::string(e.what()) + "' asset type doesn't exists", severity::warning);
        return false;
    }
}
bool asset_module::wait(const std::string& type, const std::string& name) noexcept
{
    try
    {
        return engine::builder().asset.get(type).wait(name);
    }
    catch(const std::out_of_range& e)
    {
        engine::logger().log("Failed to wait asset because '" + std::string(e.what()) + "' asset type doesn't exists", severity::warning);
        return false;
    }
}
void asset_module::dispose(const std::string& type) noexcept
{
    try
    {
        engine::builder().asset.get(type).dispose();
    }
    catch(const std::out_of_range& e)
    {
        engine::logger().log("Failed to dispose asset because '" + std::string(e.what()) + "' asset type doesn't exists", severity::warning);
    }
}
void asset_module::log(const std::string& type) const noexcept
{
    try
    {
        engine::builder().asset.get(type).log();
    }
    catch(const std::out_of_range& e)
    {
        engine::logger().log("Failed to log asset because '" + std::string(e.what()) + "' asset type doesn't exists", severity::warning);
    }
}