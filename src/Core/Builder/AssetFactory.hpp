#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/Json.hpp>
#include <Core/Utility/Reference.ipp>

#include <string>

namespace ax
{
    class AXION_CORE_API IAssetFactory
    {
    public:
        virtual ~IAssetFactory() = default;
        virtual BasicReference get(const std::string& name) noexcept = 0;
        virtual bool load(const Json& json = {}, bool validate = false) noexcept = 0;
        virtual bool loadAsync(const Json& json = {}) noexcept = 0;
        virtual bool unload(const std::string& name) noexcept = 0;
        virtual bool exists(const std::string& name) noexcept = 0;
        virtual bool wait(const std::string& name) noexcept = 0;
        virtual void dispose() noexcept = 0;
        virtual void log() const noexcept = 0;
    };

    template<typename T>
    class AXION_CORE_API AssetFactory : public IAssetFactory
    {
    public:
        BasicReference get(const std::string& name) noexcept override;
        bool load(const Json& json = {}, bool validate = false) noexcept override;
        bool loadAsync(const Json& json = {}) noexcept override;
        bool unload(const std::string& name) noexcept override;
        bool exists(const std::string& name) noexcept override;
        bool wait(const std::string& name) noexcept override;
        void dispose() noexcept override;
        void log() const noexcept override;
    };
}