#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/Path.hpp>
#include <Core/Utility/Json.hpp>
#include <Core/Utility/Macro.hpp>
#include <Core/Asset/Asset.hpp>

namespace ax
{
    class AXION_CORE_API Template : public Asset
    {
    public:
        struct Parameters
        {
            Path source;
            Json json;
        };

    public:
        ASSET_IDENTIFIER("template")
        
        Template(const std::string& name, const Parameters& parameters);

        Json merge(const Json& json) const noexcept;

    private:
        bool onLoad() noexcept override;
        bool onValidate() noexcept override;
        bool onUnload() noexcept override;

    private:
        bool loadFromSource(const Path& path) noexcept;
        bool loadFromJson(const Json& json) noexcept;

        Parameters m_parameters;
        Json m_template;
    };
}