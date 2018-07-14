#include <Core/Context/Game.hpp>

#include <Core/System/SystemManager.hpp>
#include <Core/World/World.hpp>
#include <Core/Logger/NullLogger.hpp>
#include <Core/Logger/ConsoleLogger.hpp>
#include <Core/Utility/ThreadPool.hpp>
#include <Core/Utility/LibraryLoader.hpp>
#include <Core/Context/GameContext.hpp>
#include <Core/Context/GameMode.hpp>
#include <Core/Renderer/NullRenderer.hpp>
#include <Core/Window/NullWindow.hpp>
#include <Core/Input/NullInput.hpp>

using namespace ax;

Renderer* Game::m_renderer = nullptr;
SystemManager* Game::m_systemManager = nullptr;
World* Game::m_world = nullptr;
Logger* Game::m_logger = nullptr;
ThreadPool* Game::m_threadPool = nullptr;
GameContext* Game::m_context = nullptr;
Window* Game::m_window = nullptr;
Input* Game::m_input = nullptr;

std::map<std::string, LibraryLoader> Game::m_libraryHolder;

void Game::initialize() noexcept
{
    //Context
    m_context = new GameContext();
    m_context->config().parse("Engine.ini");

    //Logger
    std::string typeLogger = Game::engine().config().getString("Logger", "type", "none");
    if(typeLogger == "console") m_logger = new ConsoleLogger();
    else m_logger = new NullLogger();

    //System
    m_systemManager = new SystemManager();

    //World
    m_world = new World();

    //Renderer
    std::string typeRenderer = Game::engine().config().getString("Renderer", "type", "none");
    typedef Renderer* (*CreateRenderer)();

    if(typeRenderer == "opengl") 
    {
        if(!m_libraryHolder["opengl"].isOpen() && !m_libraryHolder["opengl"].open("axion-opengl"))
            Game::interrupt("Failed to load dynamic library <axion-opengl>");
        CreateRenderer createRenderer;
        if(!m_libraryHolder["opengl"].getFunction<CreateRenderer>(createRenderer, "create_renderer"))
            Game::interrupt("Failed to access function <create_renderer>");
        m_renderer = createRenderer();
    }
    else m_renderer = new NullRenderer();

    //Window
    std::string typeWindow = Game::engine().config().getString("Window", "type", "none");
    typedef Window* (*CreateWindow)();

    if(typeWindow == "glfw")
    {
        if(!m_libraryHolder["glfw"].isOpen() && !m_libraryHolder["glfw"].open("axion-glfw"))
            Game::interrupt("Failed to load dynamic library <axion-glfw>");
        CreateWindow createWindow;
        if(!m_libraryHolder["glfw"].getFunction<CreateWindow>(createWindow, "create_window"))
            Game::interrupt("Failed to access function <create_window>");
        m_window = createWindow();
    }
    else m_window = new NullWindow();

    //Input
    std::string typeInput = Game::engine().config().getString("Input", "type", "none");
    typedef Input* (*CreateInput)();

    if(typeInput == "glfw") 
    {
        if(!m_libraryHolder["glfw"].isOpen() && !m_libraryHolder["glfw"].open("axion-glfw"))
            Game::interrupt("Failed to load dynamic library <axion-glfw>");
        CreateInput createInput;
        if(!m_libraryHolder["glfw"].getFunction<CreateInput>(createInput, "create_input"))
            Game::interrupt("Failed to access function <create_input>");
        m_input = createInput();
    }
    else m_input = new NullInput();

    //ThreadPool
    m_threadPool = new ThreadPool();
}
void Game::terminate() noexcept
{
    if(Game::engine().isRunning()) return;

    delete m_systemManager;
    delete m_world;

    delete m_threadPool; //ThreadPool depends on Logger

    delete m_renderer;
    delete m_input;
    delete m_window;

    delete m_logger;

    delete m_context;
}
void Game::interrupt(std::string message) noexcept
{
    Game::logger().log(message, Logger::Fatal);
    std::abort();
}

Renderer& Game::renderer() noexcept
{
    return *m_renderer;
}
SystemManager& Game::systems() noexcept
{
    return *m_systemManager;
}
World& Game::world() noexcept
{
    return *m_world;
}
Logger& Game::logger() noexcept
{
    return *m_logger;
}
ThreadPool& Game::threads() noexcept
{
    return *m_threadPool;
}
GameContext& Game::engine() noexcept
{
    return *m_context;
}
Window& Game::window() noexcept
{
    return *m_window;
}
Input& Game::input() noexcept
{
    return *m_input;
}