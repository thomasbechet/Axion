#include <Core/Asset/Asset.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Logger/LoggerModule.hpp>

#include <sstream>

using namespace ax;

Asset::Asset(const std::string& name, const std::string& identifier) : 
    m_name(name),
    m_identifier(identifier)
{

}

std::string Asset::getName() const noexcept
{
    return m_name;
}
std::string Asset::getIdentifier() const noexcept
{
    return m_identifier;
}
Asset::State Asset::getState() const noexcept
{
    return m_state.load();
}
bool Asset::isValidated() const noexcept
{
    return m_state.load() == State::Validated;
}

Asset::Information Asset::getInformation() const noexcept
{
    Information information;
    information.name = getName();
    information.identifier = getIdentifier();

    return information;
}

void Asset::logLoadError(const std::string& error) noexcept
{
    std::stringstream ss;
    ss << "Failed to load asset <" << m_identifier << "> '" << m_name << "'" << std::endl;
    ss << error;
    Engine::logger().log(ss.str(), Severity::Warning);
}
void Asset::logValidateError(const std::string& error) noexcept
{
    std::stringstream ss;
    ss << "Failed to validate asset <" << m_identifier << "> '" << m_name << "'" << std::endl;
    ss << error;
    Engine::logger().log(ss.str(), Severity::Warning);
}
void Asset::logUnloadError(const std::string& error) noexcept
{
    std::stringstream ss;
    ss << "Failed to unload asset <" << m_identifier << "> '" << m_name << "'" << std::endl;
    ss << error;
    Engine::logger().log(ss.str(), Severity::Warning);
}

bool Asset::load() noexcept
{
    bool state = onLoad();
    if(state) m_state.store(State::Loaded);
    else m_state.store(State::Failed);
    return state;
}
bool Asset::validate() noexcept
{
    bool state = onValidate();
    if(state) m_state.store(State::Validated);
    else m_state.store(State::Failed);
    return state;
}
bool Asset::unload() noexcept
{
    bool state = onUnload();
    if(state) m_state.store(State::Unloaded);
    else m_state.store(State::Failed);
    return state;
}

bool Asset::onLoad() noexcept
{
    return true;
}
bool Asset::onValidate() noexcept
{
    return true;
}
bool Asset::onUnload() noexcept
{
    return true;
}