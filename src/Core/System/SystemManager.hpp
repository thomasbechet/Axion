#pragma once

/////////////////
//HEADERS
/////////////////
#include <Core/Export.hpp>
#include <Core/Context/Game.hpp>
#include <Core/System/System.hpp>
#include <Core/Logger/Logger.hpp>

#include <vector>
#include <memory>
#include <algorithm>

namespace ax
{
    class AXION_CORE_API SystemManager : public NonCopyable
    {
    public:
        friend class Game;

        ~SystemManager();

    private:
        void start() noexcept;
        void stop() noexcept;
        void update() noexcept;

    private:
        template<typename S>
        size_t generateLocation() noexcept
        {
            m_systems.emplace_back(std::make_pair(false, std::make_unique<System>()));
            m_names.emplace_back(S::name());
            return m_systems.size() - 1;
        }
        template<typename S>
        size_t getLocation() noexcept
        {
            static size_t location = generateLocation<S>();
            return location;
        }

    public:
        void logStates() const noexcept;

        template<typename S, typename... Args>
        S& add(Args&&... args) noexcept
        {
            size_t location = getLocation<S>();
            m_systems.at(location).second.reset(new S(args...));
            m_systems.at(location).first = true;

            m_sequence.emplace_back(location);

            m_systems.at(location).second->onInitialize();

            return static_cast<S&>(*m_systems.back().second.get());
        }
        template<typename S>
        void remove() noexcept
        {
            size_t location = getLocation<S>();
            if(m_systems.at(location).first)
            {
                m_systems.at(location).first = false;
                m_systems.at(location).second.reset();

                m_systems.at(location).second->onTerminate();

                m_sequence.erase(std::remove(m_sequence.begin(), m_sequence.end(), location));
            }
            else
            {
                Game::logger().log("Try to remove nonexistent system <" + S::name() + ">", Logger::Warning);
            }
        }

        void removeAll() noexcept;

        template<typename S>
        bool exists() noexcept
        {
            size_t location = getLocation<S>();
            return m_systems.at(location).first;
        }
        template<typename S>
        S& get() noexcept
        {
            size_t location = getLocation<S>();
            if(m_systems.at(location).first)
                return static_cast<S&>(*m_systems.at(location).second.get());
            else
                Game::interrupt("Try to access nonexistent system <" + S::name() + ">");
        }


        //SEQUENCES/////////////////
        template<typename S1, typename S2>
        void sequenceSwap() noexcept
        {
            if(!m_systems.at(getLocation<S1>()).first)
                Game::interrupt("Try to swap nonexistent system <" + S1::name() + "> with system <" + S2::name() + ">");
            if(!m_systems.at(getLocation<S2>()).first)
                Game::interrupt("Try to swap nonexistent system <" + S2::name() + "> with system <" + S1::name() + ">");

            if(std::is_same<S1, S2>::value) return;

            size_t s1 = std::distance(m_sequence.begin(), std::find(m_sequence.begin(), m_sequence.end(), getLocation<S1>()));
            size_t s2 = std::distance(m_sequence.begin(), std::find(m_sequence.begin(), m_sequence.end(), getLocation<S2>()));

            std::swap(m_sequence[s1], m_sequence[s2]);
        }
        template<typename S1, typename S2>
        void sequenceBefore() noexcept
        {
            if(!m_systems.at(getLocation<S1>()).first)
                Game::interrupt("Try to move nonexistent system <" + S1::name() + "> before system <" + S2::name() + ">");
            if(!m_systems.at(getLocation<S2>()).first)
                Game::interrupt("Try to move system <" + S1::name() + "> before nonexistent system <" + S2::name() + ">");

            if(std::is_same<S1, S2>::value) return;

            size_t locationS1 = getLocation<S1>();
            size_t locationS2 = getLocation<S2>();
            m_sequence.erase(std::remove(m_sequence.begin(), m_sequence.end(), locationS1));

            auto it = std::find(m_sequence.begin(), m_sequence.end(), locationS2);
            m_sequence.emplace(it, locationS1);
        }
        template<typename S1, typename S2>
        void sequenceAfter() noexcept
        {
            if(!m_systems.at(getLocation<S1>()).first)
                Game::interrupt("Try to move nonexistent system <" + S1::name() + "> after system <" + S2::name() + ">");
            if(!m_systems.at(getLocation<S2>()).first)
                Game::interrupt("Try to move system <" + S1::name() + "> after nonexistent system <" + S2::name() + ">");

            if(std::is_same<S1, S2>::value) return;

            size_t locationS1 = getLocation<S1>();
            size_t locationS2 = getLocation<S2>();
            m_sequence.erase(std::remove(m_sequence.begin(), m_sequence.end(), locationS1));

            auto it = std::find(m_sequence.begin(), m_sequence.end(), locationS2);
            m_sequence.emplace(it + 1, locationS1);
        }
        template<typename S>
        void sequenceTop() noexcept
        {
            if(!m_systems.at(getLocation<S>()).first)
                Game::interrupt("Try to move nonexistent system <" + S::name() + ">");

            size_t location = getLocation<S>();
            m_sequence.erase(std::remove(m_sequence.begin(), m_sequence.end(), location));
            m_sequence.emplace_back(location);
        }
        template<typename S>
        void sequenceBottom() noexcept
        {
            if(!m_systems.at(getLocation<S>()).first)
                Game::interrupt("Try to move nonexistent system <" + S::name() + ">");

            size_t location = getLocation<S>();
            m_sequence.erase(std::remove(m_sequence.begin(), m_sequence.end(), location));
            m_sequence.emplace(m_sequence.begin(), location);
        }
        template<typename S>
        void sequenceMoveUp() noexcept
        {
            if(!m_systems.at(getLocation<S>()).first)
                Game::interrupt("Try to move nonexistent system <" + S::name() + ">");

            size_t location = getLocation<S>();
            auto it = std::find(m_sequence.begin(), m_sequence.end(), location);
            if(it == m_sequence.begin()) return;
            m_sequence.erase(it);
            m_sequence.emplace(it - 1, location);
        }
        template<typename S>
        void sequenceMoveDown() noexcept
        {
            if(!m_systems.at(getLocation<S>()).first)
                Game::interrupt("Try to move nonexistent system <" + S::name() + ">");

            size_t location = getLocation<S>();
            auto it = std::find(m_sequence.begin(), m_sequence.end(), location);
            if(it == m_sequence.end() - 1) return;
            m_sequence.erase(it);
            m_sequence.emplace(it + 1, location);
        }

    private:
        std::vector<std::pair<bool, std::unique_ptr<System>>> m_systems;
        std::vector<std::string> m_names;
        std::vector<size_t> m_sequence;
    };
}