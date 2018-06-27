#include <Core/System/System.hpp>

using namespace ax;

void System::active() noexcept
{
    m_active = true;
    onActive();
}
void System::disable() noexcept
{
    m_active = false;
    onDisable();
}
bool System::isActive() const noexcept
{
    return m_active;
}