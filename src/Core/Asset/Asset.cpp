#include <core/asset/asset.hpp>

#include <core/engine/engine.hpp>
#include <core/logger/logger_module.hpp>

#include <sstream>

using namespace ax;

asset::asset(const std::string& name, const std::string& identifier) : 
    m_name(name),
    m_identifier(identifier)
{

}

std::string asset::get_name() const noexcept
{
    return m_name;
}
std::string asset::get_identifier() const noexcept
{
    return m_identifier;
}
asset::state asset::get_state() const noexcept
{
    return m_state.load();
}
bool asset::is_validated() const noexcept
{
    return m_state.load() == state::validated;
}

asset::information asset::get_information() const noexcept
{
    asset::information information;
    information.name = get_name();
    information.identifier = get_identifier();

    return information;
}

void asset::log_load_error(const std::string& error) noexcept
{
    std::stringstream ss;
    ss << "Failed to load asset <" << m_identifier << "> '" << m_name << "'" << std::endl;
    ss << error;
    engine::logger().log(ss.str(), severity::warning);
}
void asset::log_validate_error(const std::string& error) noexcept
{
    std::stringstream ss;
    ss << "Failed to validate asset <" << m_identifier << "> '" << m_name << "'" << std::endl;
    ss << error;
    engine::logger().log(ss.str(), severity::warning);
}
void asset::log_unload_error(const std::string& error) noexcept
{
    std::stringstream ss;
    ss << "Failed to unload asset <" << m_identifier << "> '" << m_name << "'" << std::endl;
    ss << error;
    engine::logger().log(ss.str(), severity::Warning);
}

bool asset::load() noexcept
{
    bool state = on_load();
    if(state) m_state.store(state::loaded);
    else m_state.store(state::failed);
    return state;
}
bool asset::validate() noexcept
{
    bool state = on_validate();
    if(state) m_state.store(state::validated);
    else m_state.store(state::failed);
    return state;
}
bool asset::unload() noexcept
{
    bool state = on_unload();
    if(state) m_state.store(state::unloaded);
    else m_state.store(state::failed);
    return state;
}

bool asset::on_load() noexcept
{
    return true;
}
bool asset::on_validate() noexcept
{
    return true;
}
bool asset::on_unload() noexcept
{
    return true;
}