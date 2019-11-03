#pragma once

#include <Core/Scene/Component/ComponentList.hpp>

namespace ax
{
    template<typename C>
    std::string ComponentList<C>::identifier() const noexcept
    {
        return C::identifier;
    }
    template<typename C>
    Component& ComponentList<C>::getComponent(Id id) const noexcept
    {
        return static_cast<Component&>(get(id));
    }

    template<typename C>
    template<typename... Args>
    Id ComponentList<C>::create(const Entity& entity, Args&&... args) noexcept
    {
        return m_container.add(entity, args...);
    }

    template<typename C>
    void ComponentList<C>::destroy(Id id) noexcept
    {
        m_container.remove(id);
    }

    template<typename C>
    C& ComponentList<C>::get(Id id) const noexcept
    {
        try
        {
            return m_container.get(id);
        }
        catch(const std::out_of_range& e)
        {
            Engine::interrupt("Tried to access non valid component <" + C::identifier + "> from list with [id=" + std::to_string(id) + "]");
        }
    }

    template<typename C>
    void ComponentList<C>::addCreationCallback(std::function<void(C&)> function)
    {
        m_createFunctions.emplace_back(function);
    }
    template<typename C>
    void ComponentList<C>::removeCreationCallback(std::function<void(C&)> function)
    {
        m_createFunctions.erase(std::remove_if(
            m_createFunctions.begin(),
            m_createFunctions.end(),
            [&](const std::function<void(C&)>& f){
                return f.target() == function.target();
            }
        ), m_createFunctions.end());
    }
    template<typename C>
    void ComponentList<C>::addDestructionCallback(std::function<void(C&)> function)
    {
        m_destroyFunctions.emplace_back(function);
    }
    template<typename C>
    void ComponentList<C>::removeDestructionCallback(std::function<void(C&)> function)
    {
        m_destroyFunctions.erase(std::remove_if(
            m_destroyFunctions.begin(),
            m_destroyFunctions.end(),
            [&](const std::function<void(C&)>& f){
                return f.target() == function.target();
            }
        ), m_destroyFunctions.end());
    }

    /*template<typename C>
    typename ComponentList<C>::container::iterator ComponentList<C>::begin() noexcept
    {
        return m_container.begin();
    }
    template<typename C>
    typename ComponentList<C>::container::iterator ComponentList<C>::end() noexcept
    {
        return m_container.end();
    }*/
}