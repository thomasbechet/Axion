#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/Reference.hpp>
#include <Core/Content/Asset/Material.hpp>
#include <Core/Content/Asset/Mesh.hpp>
#include <Core/Content/Asset/Model.hpp>
#include <Core/Content/Asset/Scene.hpp>
#include <Core/Content/Asset/Shader.hpp>
#include <Core/Content/Asset/Texture.hpp>
#include <Core/Asset/Asset.hpp>

#include <string>
#include <memory>
#include <vector>

namespace ax
{
    class AXION_CORE_API Package : public Asset
    {
    public:
        struct Parameters
        {
            Path source;
            Json json;
            bool asyncLoading = true;
        };

    public:
        ASSET_IDENTIFIER("package")
        
        Package(const std::string& name, const Parameters& parameters);

    private:
        bool onLoad() noexcept override;
        bool onValidate() noexcept override;
        bool onUnload() noexcept override;

    private:
        bool loadFromSource(const Path& path) noexcept;
        bool loadFromJson(const Json& json) noexcept;

    private:
        Parameters m_parameters;

        using Item = std::tuple<std::string, std::string, BasicReference>;
        std::vector<Item> m_assets;
    };
}