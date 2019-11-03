#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/NonCopyable.hpp>

#include <atomic>
#include <string>

namespace ax
{
    class AXION_CORE_API Asset : public NonCopyable
    {
    public:
        template<typename T>
        friend class AssetManager;
        friend class AssetLoader;

    public:
        enum State
        {
            Pending,
            Loaded,
            Validated,
            Unloaded,
            Failed
        };

        struct Information
        {
            std::string name;
            std::string identifier;
        };

    public:
        Asset(const std::string& name, const std::string& identifier);
        virtual ~Asset() = default;

        std::string getName() const noexcept;
        std::string getIdentifier() const noexcept;
        State getState() const noexcept;
        bool isValidated() const noexcept;

        Information getInformation() const noexcept;

    protected:
        void logLoadError(const std::string& error) noexcept;
        void logValidateError(const std::string& error) noexcept;
        void logUnloadError(const std::string& error) noexcept;

    private:
        bool load() noexcept;
        bool validate() noexcept;
        bool unload() noexcept;

    protected:
        virtual bool onLoad() noexcept = 0;
        virtual bool onValidate() noexcept = 0;
        virtual bool onUnload() noexcept = 0;

    private:
        const std::string m_name;
        const std::string m_identifier;
        std::atomic<State> m_state {State::Pending};
    };  
}