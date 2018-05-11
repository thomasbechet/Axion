#pragma once

/////////////////////
//HEADERS
/////////////////////
#include <memory>
#include <string>
#include <Core/Export.hpp>

namespace ax
{
    class Renderer;
    class EntityManager;
    class ComponentManager;
    class Logger;
    class ThreadPool;

    class AXION_CORE_API Game
    {
    public:
        static void initialize() noexcept;
        static void terminate() noexcept;
        static void interrupt(std::string message = "") noexcept;

        static void start() noexcept;
        static void stop() noexcept;
        
        static Renderer& renderer() noexcept;
        static EntityManager& entities() noexcept;
        static ComponentManager& components() noexcept;
        static Logger& logger() noexcept;
        static ThreadPool& threads() noexcept;

    private:        
        static Renderer* m_renderer;
        static EntityManager* m_entityManager;
        static ComponentManager* m_componentManager;
        static Logger* m_logger;
        static ThreadPool* m_threadPool;
    };
}