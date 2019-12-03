#pragma once

#include <core/export.hpp>
#include <core/utility/non_copyable.hpp>

#include <atomic>
#include <string>

namespace ax
{
    class AXION_CORE_API asset : public non_copyable
    {
    public:
        template<typename T>
        friend class asset_manager;
        friend class asset_loader;

    public:
        enum state
        {
            pending,
            loaded,
            validated,
            unloaded,
            failed
        };

        struct information
        {
            std::string name;
            std::string identifier;
        };

    public:
        asset(const std::string& name, const std::string& identifier);
        virtual ~asset() = default;

        std::string get_name() const noexcept;
        std::string get_identifier() const noexcept;
        State get_state() const noexcept;
        bool is_validated() const noexcept;

        information get_information() const noexcept;

    protected:
        void log_load_error(const std::string& error) noexcept;
        void log_validate_error(const std::string& error) noexcept;
        void log_unload_error(const std::string& error) noexcept;

    private:
        bool load() noexcept;
        bool validate() noexcept;
        bool unload() noexcept;

    protected:
        virtual bool on_load() noexcept = 0;
        virtual bool on_validate() noexcept = 0;
        virtual bool on_unload() noexcept = 0;

    private:
        const std::string m_name;
        const std::string m_identifier;
        std::atomic<State> m_state {state::pending};
    };  
}