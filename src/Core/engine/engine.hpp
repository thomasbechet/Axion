#pragma once

#include <core/export.hpp>
#include <core/utility/library_loader.hpp>

#include <string>
#include <map>

namespace ax
{
    namespace detail
    {
        class asset_module;
        class builder_module;
        class context_module;
        class input_module;
        class logger_module;
        class renderer_module;
        class scene_module;
        class window_module;
        class plugin_module;
    }

    class AXION_CORE_API engine
    {
    public:
        static void initialize() noexcept;
        static void terminate() noexcept;
        [[noreturn]] static void interrupt(std::string message = "") noexcept;

        static detail::asset_module& asset() noexcept;
        static detail::builder_module& builder() noexcept;
        static detail::context_module& context() noexcept;
        static detail::input_module& input() noexcept;
        static detail::logger_module& logger() noexcept;
        static detail::renderer_module& renderer() noexcept;
        static detail::scene_module& scene() noexcept;
        static detail::window_module& window() noexcept;

    private:       
        static detail::asset_module* m_asset;
        static detail::builder_module* m_builder;
        static detail::context_module* m_context;
        static detail::input_module* m_input;
        static detail::logger_module* m_logger;
        static detail::renderer_module* m_renderer;
        static detail::scene_module* m_scene;
        static detail::window_module* m_window;

        static std::map<std::string, detail::library_loader> m_library_holder;
    };
}