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
            std::string type;
        };

    public:
        Asset(const std::string& name);
        virtual ~Asset() = default;

        std::string getName() const noexcept;
        virtual std::string getType() const noexcept = 0;
        State getState() const noexcept;
        bool isValidated() const noexcept;

        Information getInformation() const noexcept;

    private:
        bool load() noexcept;
        bool validate() noexcept;
        bool unload() noexcept;
        void error() noexcept;

    protected:
        virtual bool onLoad() noexcept = 0;
        virtual bool onValidate() noexcept = 0;
        virtual bool onUnload() noexcept = 0;
        virtual void onError() noexcept = 0;

    private:
        const std::string m_name;
        std::atomic<State> m_state {State::Pending};
    };  
}