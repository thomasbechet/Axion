#pragma once

#include <Core/Export.hpp>
#include <Core/Asset/Model.hpp>

namespace ax
{
    class AXION_CORE_API ModelManager
    {
    public:
        AssetReference<Model> operator()(std::string name) const noexcept;
        AssetReference<Model> loadFromFile(std::string name, Path path) noexcept;
        AssetReference<Model> loadFromJson(std::string name, std::string json) noexcept;
        bool unload(std::string name, bool tryUnloadMeshes = true, bool tryUnloadMaterials = true, bool tryUnloadTextures = true) noexcept;
        bool exists(std::string name) const noexcept;

        void dispose() noexcept;
        void log() const noexcept;

    private:
        AssetReference<Model> loadObjModel(std::string name, Path path) noexcept;

        std::unordered_map<std::string, std::unique_ptr<AssetHolder<Model>>> m_models;
    };
}