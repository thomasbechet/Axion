#include <Core/Asset/Asset.hpp>

using namespace ax;

Asset::Asset(const std::string& name, const std::string& type) : 
    m_name(name),
    m_type(type)
{

}

std::string Asset::getName() const noexcept
{
    return m_name;
}
std::string Asset::getType() const noexcept
{
    return m_type;
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
    information.type = getType();

    return information;
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
void Asset::error() noexcept
{
    onError();
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
void Asset::onError() noexcept
{

}