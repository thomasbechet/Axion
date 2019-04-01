#include <Core/Context/Engine.hpp>

#include <Core/System/SystemManager.hpp>
#include <Core/World/World.hpp>
#include <Core/Logger/NullLogger.hpp>
#include <Core/Logger/ConsoleLogger.hpp>
#include <Core/Utility/ThreadPool.hpp>
#include <Core/Utility/LibraryLoader.hpp>
#include <Core/Context/EngineContext.hpp>
#include <Core/Context/GameMode.hpp>
#include <Core/Renderer/NullRenderer.hpp>
#include <Core/Window/NullWindow.hpp>
#include <Core/Input/NullInput.hpp>
#include <Core/Asset/AssetManager.hpp>
#include <Core/GUI/GUI.hpp>

using namespace ax;

const std::string Engine::EngineDirectory = "../";
const std::string Engine::GameDataDirectory = "../../GameData/";
const std::string Engine::GameDirectory = "../../";

Renderer* Engine::m_renderer = nullptr;
SystemManager* Engine::m_systemManager = nullptr;
World* Engine::m_world = nullptr;
Logger* Engine::m_logger = nullptr;
ThreadPool* Engine::m_threadPool = nullptr;
EngineContext* Engine::m_context = nullptr;
Window* Engine::m_window = nullptr;
Input* Engine::m_input = nullptr;
AssetManager* Engine::m_assets = nullptr;
GUI* Engine::m_gui = nullptr;

std::map<std::string, LibraryLoader> Engine::m_libraryHolder;

void Engine::initialize() noexcept
{
    //Context
    m_context = new EngineContext();
    m_context->config().parse("../Engine.ini");

    //Logger
    std::string typeLogger = Engine::context().config().getString("Logger", "type", "none");
    if(typeLogger == "console") m_logger = new ConsoleLogger();
    else m_logger = new NullLogger();

    //Assets
    m_assets = new AssetManager();

    //System
    m_systemManager = new SystemManager();

    //World
    m_world = new World();

    //Renderer
    std::string typeRenderer = Engine::context().config().getString("Renderer", "type", "none");
    typedef Renderer* (*CreateRenderer)();

    if(typeRenderer == "opengl") 
    {
        if(!m_libraryHolder["opengl"].isOpen() && !m_libraryHolder["opengl"].open("axion-opengl"))
            Engine::interrupt("Failed to load dynamic library <axion-opengl>");
        CreateRenderer createRenderer;
        if(!m_libraryHolder["opengl"].getFunction<CreateRenderer>(createRenderer, "create_renderer"))
            Engine::interrupt("Failed to access function <create_renderer>");
        m_renderer = createRenderer();
    }
    else m_renderer = new NullRenderer();

    //Window
    std::string typeWindow = Engine::context().config().getString("Window", "type", "none");
    typedef Window* (*CreateWindow)();

    if(typeWindow == "glfw")
    {
        if(!m_libraryHolder["glfw"].isOpen() && !m_libraryHolder["glfw"].open("axion-glfw"))
            Engine::interrupt("Failed to load dynamic library <axion-glfw>");
        CreateWindow createWindow;
        if(!m_libraryHolder["glfw"].getFunction<CreateWindow>(createWindow, "create_window"))
            Engine::interrupt("Failed to access function <create_window>");
        m_window = createWindow();
    }
    else m_window = new NullWindow();

    //Input
    std::string typeInput = Engine::context().config().getString("Input", "type", "none");
    typedef Input* (*CreateInput)();

    if(typeInput == "glfw")
    {
        if(!m_libraryHolder["glfw"].isOpen() && !m_libraryHolder["glfw"].open("axion-glfw"))
            Engine::interrupt("Failed to load dynamic library <axion-glfw>");
        CreateInput createInput;
        if(!m_libraryHolder["glfw"].getFunction<CreateInput>(createInput, "create_input"))
            Engine::interrupt("Failed to access function <create_input>");
        m_input = createInput();
    }
    else m_input = new NullInput();

    //GUI
    m_gui = new GUI();

    //ThreadPool
    m_threadPool = new ThreadPool();

    ////////////////////////////////////////////////////////////////////////////////

    //Configure Logger
    Engine::logger().displayDate(Engine::context().config().getBoolean("Logger", "show_time", true));

    //Initializes engine
    Engine::window().initialize();
    Engine::input().initialize();
    Engine::renderer().initialize();
    Engine::gui().initialize();

    /////////////////////////////////////////////////////////////////////////////////

    //Create default viewport
    RendererViewportHandle defaultViewport = Engine::renderer().createViewport(Vector2f(0.0f, 0.0f), Vector2f(1.0f, 1.0f), RenderMode::ForwardPlusShading);
    Engine::renderer().setDefaultViewport(defaultViewport);

    Vector2u defaultResolution;

    if(Engine::context().config().getString("Renderer", "default_viewport_width", "default") != "default")
        defaultResolution.x = Engine::context().config().getUnsigned("Renderer", "default_viewport_width", 1920);
    else
        defaultResolution.x = Engine::window().getSize().x;

    if(Engine::context().config().getString("Renderer", "default_viewport_height", "default") != "default")
        defaultResolution.y = Engine::context().config().getUnsigned("Renderer", "default_viewport_height", 1080);
    else
        defaultResolution.y = Engine::window().getSize().y;

    defaultViewport->setResolution(defaultResolution);

    //Create default material
    MaterialParameters defaultMaterial;
    Engine::assets().material.loadFromMemory("default_material", defaultMaterial);
}
void Engine::terminate() noexcept
{
    if(Engine::context().isRunning()) return;

    //Terminates engine
    Engine::gui().terminate();
    Engine::renderer().terminate();
    Engine::input().terminate();
    Engine::window().terminate();

    delete m_systemManager;
    delete m_world;
    delete m_assets;
    delete m_threadPool; //ThreadPool depends on Logger
    delete m_gui;
    delete m_renderer;
    delete m_input;
    delete m_window;
    delete m_logger;
    delete m_context;
}
void Engine::interrupt(std::string message) noexcept
{
    Engine::logger().log(message, Logger::Fatal);
    std::abort();
}

Renderer& Engine::renderer() noexcept
{
    return *m_renderer;
}
SystemManager& Engine::systems() noexcept
{
    return *m_systemManager;
}
World& Engine::world() noexcept
{
    return *m_world;
}
Logger& Engine::logger() noexcept
{
    return *m_logger;
}
ThreadPool& Engine::threads() noexcept
{
    return *m_threadPool;
}
EngineContext& Engine::context() noexcept
{
    return *m_context;
}
Window& Engine::window() noexcept
{
    return *m_window;
}
Input& Engine::input() noexcept
{
    return *m_input;
}
AssetManager& Engine::assets() noexcept
{
    return *m_assets;
}
GUI& Engine::gui() noexcept
{
    return *m_gui;
}