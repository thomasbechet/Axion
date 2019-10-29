#include <Core/Scene/Component/ComponentManager.hpp>

using namespace ax;

void ComponentManager::destroy(ComponentHandle handle) noexcept
{
    m_componentLists.at(handle.section).get()->destroy(handle.offset);
}

Component& ComponentManager::get(ComponentHandle handle) noexcept
{
    return m_componentLists.at(handle.section).get()->getComponent(handle.offset);
}