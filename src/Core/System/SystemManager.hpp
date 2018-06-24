#pragma once

/////////////////
//HEADERS
/////////////////
#include <Core/Export.hpp>
#include <Core/System/MonothreadSystem.hpp>
#include <Core/System/MultithreadSystem.hpp>
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
        size_t generateMonothreadLocation() noexcept
        {
            m_monothread.emplace_back(std::make_pair(false, std::make_unique<MonothreadSystem>()));
            return m_monothread.size() - 1;
        }
        template<typename S>
        size_t generateMultithreadLocation() noexcept
        {
            m_multithread.emplace_back(std::make_pair(false, std::make_unique<MultithreadSystem>()));
            return m_multithread.size() - 1;
        }
        template<typename S>
        size_t getMonothreadLocation() noexcept
        {
            static size_t location = generateMonothreadLocation<S>();
            return location;
        }
        template<typename S>
        size_t getMultithreadLocation() noexcept
        {
            static size_t location = generateMultithreadLocation<S>();
            return location;
        }

    public:
        template<typename S, typename... Args>
        typename std::enable_if<std::is_base_of<MonothreadSystem, S>::value, S>::type add(Args&&... args) noexcept
        {
            size_t location = getMonothreadLocation<S>();
            m_monothread.at(location).second.reset(new S(args...));
            m_monothread.at(location).first = true;

            return static_cast<S&>(*m_monothread.back().second.get());
        }
        template<typename S, typename... Args>
        typename std::enable_if<std::is_base_of<MultithreadSystem, S>::value, S>::type add(Args&&... args) noexcept
        {
            size_t location = getMultithreadLocation<S>();
            m_multithread.at(location).second.reset(new S(args...));
            m_multithread.at(location).first = true;

            return static_cast<S&>(*m_multithread.back().second.get());
        }

        template<typename S>
        typename std::enable_if<std::is_base_of<MonothreadSystem, S>::value, S>::type remove() noexcept
        {
            size_t location = getMonothreadLocation<S>();
            if(m_monothread.at(location).first)
            {
                m_monothread.at(location).first = false;
                m_monothread.at(location).second.reset();
            }
            else
            {
                Game::logger().log("Try to remove nonexistent system <" + S::name() + ">", Logger::Warning);
            }
        }
        template<typename S>
        typename std::enable_if<std::is_base_of<MultithreadSystem, S>::value, S>::type remove() noexcept
        {
            size_t location = getMultithreadLocation<S>();
            if(m_monothread.at(location).first)
            {
                m_multithread.at(location).first = false;
                m_multithread.at(location).second.reset();
            }
            else
            {
                Game::logger().log("Try to remove nonexistent system <" + S::name() + ">", Logger::Warning);
            }
        }
        
        template<typename S>
        typename std::enable_if<std::is_base_of<MonothreadSystem, S>::value, S>::type& get() noexcept
        {
            size_t location = getMonothreadLocation<S>();
            if(m_monothread.at(location).first)
                return static_cast<S&>(*m_monothread.at(location).second.get());
            else
                Game::interrupt("Try to access nonexistent system <" + S::name() + ">");
        }
        template<typename S>
        typename std::enable_if<std::is_base_of<MultithreadSystem, S>::value, S>::type& get() noexcept
        {
            size_t location = getMultithreadLocation<S>();
            if(m_multithread.at(location).first)
                return static_cast<S&>(*m_multithread.at(location).second.get());
            else
                Game::interrupt("Try to access nonexistent system <" + S::name() + ">");
        }
        
    private:
        std::vector<std::pair<bool, std::unique_ptr<MonothreadSystem>>> m_monothread;
        std::vector<std::pair<bool, std::unique_ptr<MultithreadSystem>>> m_multithread;
        //std::vector<std::unique_ptr<AsynchronousSystem>> m_asynchronous;
    };
}