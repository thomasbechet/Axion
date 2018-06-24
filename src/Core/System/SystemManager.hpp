#pragma once

/////////////////
//HEADERS
/////////////////
#include <Core/Export.hpp>
#include <Core/System/System.hpp>
#include <Core/Logger/Logger.hpp>

#include <vector>
#include <memory>

namespace ax
{
    class AXION_CORE_API SystemManager : public NonCopyable
    {
    public:
        friend class Game;

    private:
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
        template<typename S, typename... Args>
        S& add(Args&&... args) noexcept
        {
            size_t location = getLocation<S>();
            m_systems.at(location).second.reset(new S(args...));
            m_systems.at(location).first = true;

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
            }
            else
            {
                Game::logger().log("Try to remove nonexistent system <" + S::name() + ">", Logger::Warning);
            }
        }

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

        void logStates() const noexcept;

    private:
        std::vector<std::pair<bool, std::unique_ptr<System>>> m_systems;
        std::vector<std::string> m_names;
        std::vector<std::string> m_sequence;
    };
}