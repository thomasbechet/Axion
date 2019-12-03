#pragma once

#include <core/export.hpp>
#include <core/asset/asset_loader.hpp>
#include <core/logger/logger_module.hpp>
#include <core/utility/reference.ipp>
#include <core/engine/engine.hpp>

#include <mutex>
#include <unordered_map>
#include <sstream>
#include <iomanip>

namespace ax
{
    class AXION_CORE_API asset_manager_interface
    {
    public:
        virtual ~asset_manager_interface() = default;
        virtual void dispose() noexcept = 0;
        virtual void log() const noexcept = 0;
    };

    template<typename type>
    class AXION_CORE_API asset_manager : public asset_manager_interface
    {
    public:
        asset_manager(asset_loader& loader);

        //MAIN THREAD ONLY
        reference<type> get(const std::string& name) const noexcept;
        //ANY THREAD (validate = ONLY MAIN THREAD)
        bool load(const std::string& name, const typename type::parameters& parameters, bool validate = false) noexcept;
        //ANY THREAD
        bool load_async(const std::string& name, const typename type::parameters& parameters) noexcept;
        //ANY THREAD
        bool exists(const std::string& name) const noexcept;
        //MAIN THREAD ONLY
        bool wait(const std::string& name) const noexcept;
        //MAIN THREAD ONLY
        bool unload(const std::string& name) noexcept;

        //MAIN THREAD ONLY
        void dispose() noexcept override;
        //MAIN THREAD ONLY
        void log() const noexcept override;
        
    private:
        bool exists_not_safe(const std::string& name) const noexcept;

    private:
        std::unordered_map<std::string, std::unique_ptr<type>> m_assets;
        std::unordered_map<std::string, std::unique_ptr<reference_tracker<t>>> m_trackers;
        mutable std::mutex m_mutex;
        asset_loader& m_loader;
    };
}