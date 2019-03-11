#pragma once

/////////////////////
//HEADERS
/////////////////////
#include <Core/Export.hpp>
#include <Core/Utility/LibraryLoader.hpp>

#include <memory>
#include <string>
#include <map>

namespace ax
{
    class GameMode;
    class Renderer;
    class SystemManager;
    class World;
    class Logger;
    class ThreadPool;
    class EngineContext;
    class Window;
    class Input;
    class AssetManager;

    class AXION_CORE_API Engine
    {
    public:
        friend class EngineContext;

    public:
        static void initialize() noexcept;
        static void terminate() noexcept;
        static void interrupt(std::string message = "") noexcept;
        
        static EngineContext& context() noexcept;
        static Renderer& renderer() noexcept;
        static SystemManager& systems() noexcept;
        static World& world() noexcept;
        static Logger& logger() noexcept;
        static ThreadPool& threads() noexcept;
        static Window& window() noexcept;
        static Input& input() noexcept;
        static AssetManager& assets() noexcept;

        static const std::string EngineDirectory; //   Game/Engine/
        static const std::string GameDataDirectory; // Game/GameData/
        static const std::string GameDirectory;   //   Game/

    private:        
        static Renderer* m_renderer;
        static SystemManager* m_systemManager;
        static World* m_world;
        static Logger* m_logger;
        static ThreadPool* m_threadPool;
        static EngineContext* m_context;
        static Window* m_window;
        static Input* m_input;
        static AssetManager* m_assets;

        static std::map<std::string, LibraryLoader> m_libraryHolder;
    };
}