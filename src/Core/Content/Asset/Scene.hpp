#pragma once

#include <Core/Export.hpp>
#include <Core/Asset/Asset.hpp>
#include <Core/Utility/Path.hpp>
#include <Core/Utility/Json.hpp>
#include <Core/Utility/Macro.hpp>

#include <string>

namespace ax
{
    class AXION_CORE_API Scene : public Asset
    {
    public:
        struct Parameters
        {
            Path source;
            Json json;
        };

        enum InsertionMethod
        {
            Override,
            Additive
        };

    public:
        ASSET_IDENTIFIER("scene")
        
        Scene(const std::string& name, const Parameters& parameters);

        InsertionMethod getInsertionMethod() const noexcept;
        std::string getGameMode() const noexcept;
        std::vector<std::string> getSystems() const noexcept;
        const std::vector<const std::reference_wrapper<Json>&>& getEntities() const noexcept;

    private:
        bool onLoad() noexcept override;
        bool onValidate() noexcept override;
        bool onUnload() noexcept override;

    private:
        Parameters m_parameters;

        InsertionMethod m_insertionMethod;
    };
}