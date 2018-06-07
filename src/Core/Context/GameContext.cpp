#include <Core/Context/GameContext.hpp>

using namespace ax;

ConfigParser& GameContext::config() noexcept
{
    return m_configParser;
}