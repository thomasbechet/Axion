#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/LibraryLoader.hpp>

#include <memory>
#include <string>
#include <map>

namespace ax
{
    class AssetModule;
    class BuilderModule;
    class ContextModule;
    class InputModule;
    class LoggerModule;
    class RendererModule;
    class SceneModule;
    class WindowModule;

    class AXION_CORE_API Engine
    {
    public:
        static void initialize() noexcept;
        static void terminate() noexcept;
        [[noreturn]] static void interrupt(std::string message = "") noexcept;
        
        static AssetModule& asset() noexcept;
        static BuilderModule& builder() noexcept;
        static ContextModule& context() noexcept;
        static InputModule& input() noexcept;
        static LoggerModule& logger() noexcept;
        static RendererModule& renderer() noexcept;
        static SceneModule& scene() noexcept;
        static WindowModule& window() noexcept;

        static inline const std::string EngineDirectory = "..";                // => Game/Engine/
        static inline const std::string GameDataDirectory = "../../GameData/"; // => Game/GameData/
        static inline const std::string GameDirectory = "../..";               // => Game/

    private:       
        static AssetModule* m_asset;
        static BuilderModule* m_builder;
        static ContextModule* m_context;
        static InputModule* m_input;
        static LoggerModule* m_logger;
        static RendererModule* m_renderer;
        static SceneModule* m_scene;
        static WindowModule* m_window;

        static std::map<std::string, LibraryLoader> m_libraryHolder;
    };
}