#include <Core/Builder/SystemFactories.hpp>

using namespace ax;

ISystemFactory& SystemFactories::get(const std::string& identifier) noexcept
{
    return *m_factories.at(identifier).get();
}