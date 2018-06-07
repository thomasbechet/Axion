#pragma once

/////////////////
//HEADERS
/////////////////
#include <Core/Export.hpp>
#include <Core/System/MonothreadSystem.hpp>
#include <Core/System/MultithreadSystem.hpp>

#include <vector>
#include <memory>

namespace ax
{
    class AXION_CORE_API SystemManager : public NonCopyable
    {
    public:
        /*template<typename S, typename... Args>
        S& add(Args&&... args)
        {
            if(std::is_base_of<MonothreadSystem, S>::value)
            {
                m_monothread.emplace_back(std::make_unique<S>(args...));
                m_monothread.back().m_id = m_monothread.size() - 1;
                return static_cast<S&>(m_monothread.back());
            }   
            else if(std::is_base_of<MultithreadSystem, S>::value)
            {
                m_multithread.emplace_back(std::make_unique<S>(args...));
                m_multithread.back().m_id = m_multithread.size() - 1;
                return static_cast<S&>(m_multithread.back());
            }
        }
        template<typename S>
        void remove(S& system)
        {
        std::vector<std::unique_ptr<MonothreadSystem>> m_monothread;
        std::vector<std::unique_ptr<MultithreadSystem>> m_multithread;
        //std::vector<std::unique_ptr<AsynchronousSystem>> m_asynchronous;*/
    };
}