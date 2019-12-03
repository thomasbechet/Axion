#pragma once

#include <core/export.hpp>
#include <core/engine/module.hpp>
#include <core/utility/path.hpp>
#include <core/utility/json.hpp>
#include <core/asset/asset_loader.hpp>
#include <core/asset/asset_manager.ipp>

#include <mutex>
#include <typeinfo>
#include <typeindex>

namespace ax::detail
{
    class AXION_CORE_API asset_module : public module
    {
    public:
        ~asset_module();

    public:
        void initialize() noexcept override {}
        void terminate() noexcept override {}

    private:
        template<typename type>
        asset_manager<type>& get_manager() noexcept;

        std::vector<std::unique_ptr<asset_manager_interface>> m_managers;
        std::unordered_map<std::type_index, size_t> m_indexes;
        std::mutex m_location_mutex;

    public:
        void dispose() noexcept;
        void log() const noexcept;

        template<typename type>
        reference<type> get(const std::string& name) noexcept;
        template<typename type>
        bool load(const std::string& name, const typename type::parameters& parameters, bool validate = false) noexcept;
        template<typename type>
        bool load_async(const std::string& name, const typename type::parameters& parameters) noexcept;
        template<typename type>
        bool unload(const std::string& name) noexcept;
        template<typename type>
        bool exists(const std::string& name) noexcept;
        template<typename type>
        bool wait(const std::string& name) noexcept;
        template<typename type>
        void dispose() noexcept;
        template<typename type>
        void log() noexcept;

        basic_reference get(const std::string& type, const std::string& name) noexcept;
        bool load(const json& json = {}, bool validate = false) noexcept;
        bool load_async(const json& json = {}) noexcept;
        bool unload(const std::string& type, const std::string& name) noexcept;
        bool exists(const std::string& type, const std::string& name) const noexcept;
        bool wait(const std::string& type, const std::string& name) noexcept;
        void dispose(const std::string& type) noexcept;
        void log(const std::string& type) const noexcept;

        asset_loader loader;
    };
}