#pragma once

/////////////////////
//HEADERS
/////////////////////
#include <memory>
#include <string>
#include <Core/Export.hpp>

namespace ax
{
    class GameMode;
    class Renderer;
    class SystemManager;
    class World;
    class Logger;
    class ThreadPool;
    class GameContext;
    class Window;
    class Input;

    class AXION_CORE_API Game
    {
    public:
        friend class GameContext;

    private:
        static void run() noexcept;

    public:
        static void initialize() noexcept;
        static void terminate() noexcept;
        static void interrupt(std::string message = "") noexcept;
        
        static Renderer& renderer() noexcept;
        static SystemManager& systems() noexcept;
        static World& world() noexcept;
        static Logger& logger() noexcept;
        static ThreadPool& threads() noexcept;
        static GameContext& engine() noexcept;
        static Window& window() noexcept;
        static Input& input() noexcept;

    private:        
        static Renderer* m_renderer;
        static SystemManager* m_systemManager;
        static World* m_world;
        static Logger* m_logger;
        static ThreadPool* m_threadPool;
        static GameContext* m_context;
        static Window* m_window;
        static Input* m_input;
    };
}