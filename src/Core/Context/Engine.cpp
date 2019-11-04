#include <Core/Context/Engine.hpp>

#include <Core/Scene/System/SystemManager.hpp>
#include <Core/Scene/SceneModule.hpp>
#include <Core/Logger/NullLoggerModule.hpp>
#include <Core/Logger/ConsoleLoggerModule.hpp>
#include <Core/Utility/LibraryLoader.hpp>
#include <Core/Context/ContextModule.hpp>
#include <Core/Scene/GameMode/GameMode.hpp>
#include <Core/Renderer/NullRendererModule.hpp>
#include <Core/Window/NullWindowModule.hpp>
#include <Core/Input/NullInputModule.hpp>
#include <Core/Asset/AssetModule.hpp>
#include <Core/Scene/UI/UIManager.hpp>
#include <Core/Builder/BuilderModule.hpp>

using namespace ax;

const std::string Engine::EngineDirectory = "..";
const std::string Engine::GameDataDirectory = "../../GameData";
const std::string Engine::GameDirectory = "../..";

AssetModule* Engine::m_asset = nullptr;
BuilderModule* Engine::m_builder = nullptr;
ContextModule* Engine::m_context = nullptr;
InputModule* Engine::m_input = nullptr;
LoggerModule* Engine::m_logger = nullptr;
RendererModule* Engine::m_renderer = nullptr;
SceneModule* Engine::m_scene = nullptr;
WindowModule* Engine::m_window = nullptr;

std::map<std::string, LibraryLoader> Engine::m_libraryHolder;

void Engine::initialize() noexcept
{
    //Builder
    m_builder = new BuilderModule();

    //Context
    m_context = new ContextModule();
    m_context->config.parse("../Engine.ini");

    //Logger
    std::string typeLogger = Engine::context().config.getString("Logger", "type", "none");
    if(typeLogger == "console") m_logger = new ConsoleLoggerModule();
    else m_logger = new NullLoggerModule();

    //Renderer
    std::string typeRenderer = Engine::context().config.getString("Renderer", "type", "none");
    typedef RendererModule* (*CreateRenderer)();

    if(typeRenderer == "opengl") 
    {
        if(!m_libraryHolder["opengl"].isOpen() && !m_libraryHolder["opengl"].open("axion-opengl"))
            Engine::interrupt("Failed to load dynamic library <axion-opengl>");
        CreateRenderer createRenderer;
        if(!m_libraryHolder["opengl"].getFunction<CreateRenderer>(createRenderer, "create_renderer"))
            Engine::interrupt("Failed to access function <create_renderer>");
        m_renderer = createRenderer();
    }
    else m_renderer = new NullRendererModule();

    //Window
    std::string typeWindow = Engine::context().config.getString("Window", "type", "none");
    typedef WindowModule* (*CreateWindow)();

    if(typeWindow == "glfw")
    {
        if(!m_libraryHolder["glfw"].isOpen() && !m_libraryHolder["glfw"].open("axion-glfw"))
            Engine::interrupt("Failed to load dynamic library <axion-glfw>");
        CreateWindow createWindow;
        if(!m_libraryHolder["glfw"].getFunction<CreateWindow>(createWindow, "create_window"))
            Engine::interrupt("Failed to access function <create_window>");
        m_window = createWindow();
    }
    else m_window = new NullWindowModule();

    //Input
    std::string typeInput = Engine::context().config.getString("Input", "type", "none");
    typedef InputModule* (*CreateInput)();

    if(typeInput == "glfw")
    {
        if(!m_libraryHolder["glfw"].isOpen() && !m_libraryHolder["glfw"].open("axion-glfw"))
            Engine::interrupt("Failed to load dynamic library <axion-glfw>");
        CreateInput createInput;
        if(!m_libraryHolder["glfw"].getFunction<CreateInput>(createInput, "create_input"))
            Engine::interrupt("Failed to access function <create_input>");
        m_input = createInput();
    }
    else m_input = new NullInputModule();

    //Assets
    m_asset = new AssetModule();

    //Scene
    m_scene = new SceneModule();

    ////////////////////////////////////////////////////////////////////////////////

    //Configure Logger
    Engine::logger().initialize();
    Engine::logger().displayDate(Engine::context().config.getBoolean("Logger", "show_time", true));

    //Initializes engine
    Engine::window().initialize();
    Engine::input().initialize();
    Engine::renderer().initialize();

    /////////////////////////////////////////////////////////////////////////////////

    //Create default viewport
    Vector2u defaultResolution;

    if(Engine::context().config.getString("Renderer", "default_viewport_width", "default") != "default")
        defaultResolution.x = Engine::context().config.getUnsigned("Renderer", "default_viewport_width", 1920);
    else
        defaultResolution.x = Engine::window().getSize().x;

    if(Engine::context().config.getString("Renderer", "default_viewport_height", "default") != "default")
        defaultResolution.y = Engine::context().config.getUnsigned("Renderer", "default_viewport_height", 1080);
    else
        defaultResolution.y = Engine::window().getSize().y;

    Rectf viewport;
    viewport.bottom = 0.0f;
    viewport.left = 0.0f;
    viewport.width = 1.0f;
    viewport.height = 1.0f;

    RendererGUIViewportHandle defaultViewport = Engine::renderer().createViewport(viewport, defaultResolution, RenderMode::Wireframe);
    Engine::renderer().setDefaultViewport(defaultViewport);

    //Create default material
    Material::Parameters defaultMaterial;
    Engine::asset().material.load("default_material", defaultMaterial);
}
void Engine::terminate() noexcept
{
    if(Engine::context().isRunning()) return;

    //Terminates engine
    Engine::renderer().terminate();
    Engine::input().terminate();
    Engine::window().terminate();

    //Shutdown logger
    Engine::logger().terminate();

    delete m_scene;
    delete m_asset;
    delete m_renderer;
    delete m_input;
    delete m_window;
    delete m_logger;
    delete m_builder;
    delete m_context;
}
void Engine::interrupt(std::string message) noexcept
{
    Engine::logger().log(message, Severity::Fatal);
    Engine::logger().flush();
    std::abort();
}

AssetModule& Engine::asset() noexcept
{
    return *m_asset;
}
BuilderModule& Engine::builder() noexcept
{
    return *m_builder;
}
ContextModule& Engine::context() noexcept
{
    return *m_context;
}
InputModule& Engine::input() noexcept
{
    return *m_input;
}
LoggerModule& Engine::logger() noexcept
{
    return *m_logger;
}
RendererModule& Engine::renderer() noexcept
{
    return *m_renderer;
}
SceneModule& Engine::scene() noexcept
{
    return *m_scene;
}
WindowModule& Engine::window() noexcept
{
    return *m_window;
}