#include <Core/Scene/Entity/Entity.hpp>

#include <Core/Scene/SceneModule.hpp>

using namespace ax;

void Entity::removeAll() noexcept
{
    for(auto& it : m_handles)
        Engine::scene().component.destroy(it);
        
    m_handles.clear();
}