#pragma once

#include <Core/Scene/System/SystemManager.hpp>

#include <Core/Engine/Engine.hpp>
#include <Core/Logger/LoggerModule.hpp>

#include <algorithm>

namespace ax
{
    template<typename S>
    size_t SystemManager::generateLocation() noexcept
    {
        m_systems.emplace_back(std::make_pair(false, std::make_unique<System>()));
        m_names.emplace_back(S::identifier);

        return m_systems.size() - 1;
    }
    template<typename S>
    size_t SystemManager::getLocation() noexcept
    {
        static size_t location = generateLocation<S>();
        return location;
    }

    template<typename S, typename... Args>
    S& SystemManager::add(Args&&... args) noexcept
    {
        size_t location = getLocation<S>();

        //If the systems already exists, return the system (no copy)
        if(m_systems.at(location).first)
            return static_cast<S&>(*m_systems.at(location).second.get());

        m_systems.at(location).second.reset(new S(args...));
        m_systems.at(location).first = true;

        m_sequence.emplace_back(location);

        m_systems.at(location).second->onInitialize();

        return static_cast<S&>(*m_systems.at(location).second.get());
    }
    template<typename S>
    void SystemManager::remove() noexcept
    {
        size_t location = getLocation<S>();
        if(m_systems.at(location).first)
        {
            m_systems.at(location).second->onTerminate();

            m_systems.at(location).first = false;
            m_systems.at(location).second.reset();

            m_sequence.erase(std::remove(m_sequence.begin(), m_sequence.end(), location));
        }
        else
        {
            Engine::logger().log("Try to remove nonexistent system <" + S::identifier + ">", Severity::Warning);
        }
    }

    template<typename S>
    bool SystemManager::exists() noexcept
    {
        size_t location = getLocation<S>();
        return m_systems.at(location).first;
    }
    template<typename S>
    S& SystemManager::get() noexcept
    {
        size_t location = getLocation<S>();
        if(m_systems.at(location).first)
            return static_cast<S&>(*m_systems.at(location).second.get());
        else
            Engine::interrupt("Try to access nonexistent system <" + S::identifier + ">");
    }

    //SEQUENCES/////////////////
    template<typename S1, typename S2>
    void SystemManager::sequenceSwap() noexcept
    {
        if(!m_systems.at(getLocation<S1>()).first)
            Engine::interrupt("Try to swap nonexistent system <" + S1::identifier + "> with system <" + S2::identifier + ">");
        if(!m_systems.at(getLocation<S2>()).first)
            Engine::interrupt("Try to swap nonexistent system <" + S2::identifier + "> with system <" + S1::identifier + ">");

        if(std::is_same<S1, S2>::value) return;

        size_t s1 = std::distance(m_sequence.begin(), std::find(m_sequence.begin(), m_sequence.end(), getLocation<S1>()));
        size_t s2 = std::distance(m_sequence.begin(), std::find(m_sequence.begin(), m_sequence.end(), getLocation<S2>()));

        std::swap(m_sequence[s1], m_sequence[s2]);
    }
    template<typename S1, typename S2>
    void SystemManager::sequenceBefore() noexcept
    {
        if(!m_systems.at(getLocation<S1>()).first)
            Engine::interrupt("Try to move nonexistent system <" + S1::identifier + "> before system <" + S2::identifier + ">");
        if(!m_systems.at(getLocation<S2>()).first)
            Engine::interrupt("Try to move system <" + S1::identifier + "> before nonexistent system <" + S2::identifier + ">");

        if(std::is_same<S1, S2>::value) return;

        size_t locationS1 = getLocation<S1>();
        size_t locationS2 = getLocation<S2>();
        m_sequence.erase(std::remove(m_sequence.begin(), m_sequence.end(), locationS1));

        auto it = std::find(m_sequence.begin(), m_sequence.end(), locationS2);
        m_sequence.emplace(it, locationS1);
    }
    template<typename S1, typename S2>
    void SystemManager::sequenceAfter() noexcept
    {
        if(!m_systems.at(getLocation<S1>()).first)
            Engine::interrupt("Try to move nonexistent system <" + S1::identifier + "> after system <" + S2::identifier + ">");
        if(!m_systems.at(getLocation<S2>()).first)
            Engine::interrupt("Try to move system <" + S1::identifier + "> after nonexistent system <" + S2::identifier + ">");

        if(std::is_same<S1, S2>::value) return;

        size_t locationS1 = getLocation<S1>();
        size_t locationS2 = getLocation<S2>();
        m_sequence.erase(std::remove(m_sequence.begin(), m_sequence.end(), locationS1));

        auto it = std::find(m_sequence.begin(), m_sequence.end(), locationS2);
        m_sequence.emplace(it + 1, locationS1);
    }
    template<typename S>
    void SystemManager::sequenceTop() noexcept
    {
        if(!m_systems.at(getLocation<S>()).first)
            Engine::interrupt("Try to move nonexistent system <" + S::identifier + ">");

        size_t location = getLocation<S>();
        m_sequence.erase(std::remove(m_sequence.begin(), m_sequence.end(), location));
        m_sequence.emplace_back(location);
    }
    template<typename S>
    void SystemManager::sequenceBottom() noexcept
    {
        if(!m_systems.at(getLocation<S>()).first)
            Engine::interrupt("Try to move nonexistent system <" + S::identifier + ">");

        size_t location = getLocation<S>();
        m_sequence.erase(std::remove(m_sequence.begin(), m_sequence.end(), location));
        m_sequence.emplace(m_sequence.begin(), location);
    }
    template<typename S>
    void SystemManager::sequenceMoveUp() noexcept
    {
        if(!m_systems.at(getLocation<S>()).first)
            Engine::interrupt("Try to move nonexistent system <" + S::identifier + ">");

        size_t location = getLocation<S>();
        auto it = std::find(m_sequence.begin(), m_sequence.end(), location);
        if(it == m_sequence.begin()) return;
        m_sequence.erase(it);
        m_sequence.emplace(it - 1, location);
    }
    template<typename S>
    void SystemManager::sequenceMoveDown() noexcept
    {
        if(!m_systems.at(getLocation<S>()).first)
            Engine::interrupt("Try to move nonexistent system <" + S::identifier + ">");

        size_t location = getLocation<S>();
        auto it = std::find(m_sequence.begin(), m_sequence.end(), location);
        if(it == m_sequence.end() - 1) return;
        m_sequence.erase(it);
        m_sequence.emplace(it + 1, location);
    }
}