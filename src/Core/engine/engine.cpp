#include <core/engine/engine.hpp>

#include <core/scene/system/_system_manager.hpp>
#include <core/scene/scene_module.hpp>
#include <core/logger/null_logger_module.hpp>
#include <core/logger/console_logger_module.hpp>
#include <core/utility/library_loader.hpp>
#include <core/context/context_module.hpp>
#include <core/scene/game_mode/_game_mode.hpp>
#include <core/renderer/null_renderer_module.hpp>
#include <core/window/null_window_module.hpp>
#include <core/input/null_input_module.hpp>
#include <core/asset/asset_module.hpp>
#include <core/scene/ui/ui_manager.hpp>
#include <core/builder/builder_module.hpp>

using namespace ax;
using namespace ax::detail;

asset_module* engine::m_asset = nullptr;
builder_module* engine::m_builder = nullptr;
context_module* engine::m_context = nullptr;
input_module* engine::m_input = nullptr;
logger_module* engine::m_logger = nullptr;
renderer_module* engine::m_renderer = nullptr;
scene_module* engine::m_scene = nullptr;
window_module* engine::m_window = nullptr;

std::map<std::string, library_loader> engine::m_library_holder;

void engine::initialize() noexcept
{
    //Builder
    m_builder = new builder_module();

    //Context
    m_context = new context_module("../_engine.ini");

    //Logger
    std::string type_logger = engine::context().config.get_string("_logger", "type", "none");
    if(type_logger == "console") m_logger = new console_logger_module();
    else m_logger = new null_logger_module();

    //Renderer
    std::string type_renderer = engine::context().config.get_string("_renderer", "type", "none");
    typedef renderer_module* (*create_renderer)();

    if(type_renderer == "opengl") 
    {
        if(!m_library_holder["opengl"].is_open() && !m_library_holder["opengl"].open("axion-opengl"))
            Engine::interrupt("Failed to load dynamic library <axion-opengl>");
        create_renderer create_renderer;
        if(!m_libraryHolder["opengl"].get_function<create_renderer>(create_renderer, "create_renderer"))
            Engine::interrupt("Failed to access function <create_renderer>");
        m_renderer = create_renderer();
    }
    else m_renderer = new null_renderer_module();

    //Window
    std::string type_window = engine::context().config.get_string("_window", "type", "none");
    typedef window_module* (*create_window)();

    if(type_window == "glfw")
    {
        if(!m_library_holder["glfw"].is_open() && !m_library_holder["glfw"].open("axion-glfw"))
            Engine::interrupt("Failed to load dynamic library <axion-glfw>");
        create_window create_window;
        if(!m_libraryHolder["glfw"].get_function<create_window>(create_window, "create_window"))
            Engine::interrupt("Failed to access function <create_window>");
        m_window = create_window();
    }
    else m_window = new null_window_module();

    //Input
    std::string type_input = engine::context().config.get_string("_input", "type", "none");
    typedef input_module* (*create_input)();

    if(type_input == "glfw")
    {
        if(!m_library_holder["glfw"].is_open() && !m_library_holder["glfw"].open("axion-glfw"))
            Engine::interrupt("Failed to load dynamic library <axion-glfw>");
        create_input create_input;
        if(!m_libraryHolder["glfw"].get_function<create_input>(create_input, "create_input"))
            Engine::interrupt("Failed to access function <create_input>");
        m_input = create_input();
    }
    else m_input = new null_input_module();

    //Assets
    m_asset = new asset_module();

    //Scene
    m_scene = new scene_module();

    ////////////////////////////////////////////////////////////////////////////////

    //Initializes engine
    engine::logger().initialize();
    engine::logger().display_date(_engine::context().config.get_boolean("logger", "show_time", true));
    engine::context().initialize();
    engine::window().initialize();
    engine::input().initialize();
    engine::renderer().initialize();

    /////////////////////////////////////////////////////////////////////////////////

    //Create default viewport
    Vector2u default_resolution;

    if(engine::context().config.get_string("renderer", "default_viewport_width", "default") != "default")
        default_resolution.x = engine::context().config.get_unsigned("_renderer", "default_viewport_width", 1920);
    else
        default_resolution.x = engine::window().get_size().x;

    if(engine::context().config.get_string("renderer", "default_viewport_height", "default") != "default")
        default_resolution.y = engine::context().config.get_unsigned("renderer", "default_viewport_height", 1080);
    else
        default_resolution.y = engine::window().get_size().y;

    rectf viewport;
    viewport.bottom = 0.0f;
    viewport.left = 0.0f;
    viewport.width = 1.0f;
    viewport.height = 1.0f;

    renderer_gui_viewport_handle default_viewport = engine::renderer().create_viewport(viewport, default_resolution, render_mode::wireframe);
    engine::renderer().setDefaultViewport(default_viewport);

    //Create default material
    material_asset::parameters default_material;
    engine::asset().load<material_asset>(material_asset::default, default_material);
}
void engine::terminate() noexcept
{
    if(engine::context().is_running()) return;

    //Terminates engine
    engine::renderer().terminate();
    engine::input().terminate();
    engine::window().terminate();
    engine::context().terminate();
    engine::logger().terminate();

    delete m_scene;
    delete m_asset;
    delete m_renderer;
    delete m_input;
    delete m_window;
    delete m_logger;
    delete m_builder;
    delete m_context;
}
void engine::interrupt(std::string message) noexcept
{
    engine::logger().log(message, severity::fatal);
    engine::logger().flush();
    std::abort();
}

asset_module& engine::asset() noexcept
{
    return *m_asset;
}
builder_module& engine::builder() noexcept
{
    return *m_builder;
}
context_module& engine::context() noexcept
{
    return *m_context;
}
input_module& engine::input() noexcept
{
    return *m_input;
}
logger_module& engine::logger() noexcept
{
    return *m_logger;
}
renderer_module& engine::renderer() noexcept
{
    return *m_renderer;
}
scene_module& engine::scene() noexcept
{
    return *m_scene;
}
window_module& engine::window() noexcept
{
    return *m_window;
}