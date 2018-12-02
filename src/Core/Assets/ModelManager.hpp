#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>

namespace ax
{
    class AXION_CORE_API ModelManager
    {
    public:
        AssetReference<Model> operator()(std::string name) const noexcept;
        AssetReference<Model> create(std::string name, Path path) noexcept;
        bool destroy(std::string name, bool tryUnloadMeshes = true, bool tryUnloadMaterials = true, bool tryUnloadTextures = true) noexcept;
        bool exists(std::string name) const noexcept;

        void dispose() noexcept;
        void log() const noexcept;

    private:
        AssetReference<Model> loadObjModel(std::string name, Path path) noexcept;

        std::unordered_map<std::string, std::unique_ptr<AssetHolder<Model>>> m_models;
    };
}