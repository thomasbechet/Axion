#pragma once

#include <core/export.hpp>
#include <core/utility/json.hpp>
#include <core/utility/reference.ipp>

#include <string>

namespace ax
{
    class AXION_CORE_API asset_factory_interface
    {
    public:
        virtual ~asset_factory_interface() = default;
        virtual basic_reference get(const std::string& name) noexcept = 0;
        virtual bool load(const json& json = {}, bool validate = false) noexcept = 0;
        virtual bool load_async(const json& json = {}) noexcept = 0;
        virtual bool unload(const std::string& name) noexcept = 0;
        virtual bool exists(const std::string& name) noexcept = 0;
        virtual bool wait(const std::string& name) noexcept = 0;
        virtual void dispose() noexcept = 0;
        virtual void log() const noexcept = 0;
    };

    template<typename type>
    class AXION_CORE_API asset_factory : public asset_factory_interface
    {
    public:
        basic_reference get(const std::string& name) noexcept override;
        bool load(const json& json = {}, bool validate = false) noexcept override;
        bool load_async(const json& json = {}) noexcept override;
        bool unload(const std::string& name) noexcept override;
        bool exists(const std::string& name) noexcept override;
        bool wait(const std::string& name) noexcept override;
        void dispose() noexcept override;
        void log() const noexcept override;
    };
}