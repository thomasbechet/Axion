#pragma once

//////////////
//HEADERS
//////////////
#include <Core/Export.hpp>
#include <Core/Assets/Mesh.hpp>
#include <Core/Assets/Material.hpp>
#include <Core/Utility/Path.hpp>

#include <unordered_map>
#include <memory>
#include <string>
#include <vector>

namespace ax
{
    struct AXION_CORE_API Model
    {
        std::string name;

        std::vector<std::shared_ptr<const Mesh>> meshes;
        std::vector<std::shared_ptr<const Material>> materials;
    };

    class AXION_CORE_API ModelManager
    {
    public:
        std::shared_ptr<const Model> operator()(std::string name) const noexcept;
        std::shared_ptr<const Model> load(std::string name, Path path) noexcept;
        bool unload(std::string name, bool tryUnloadMaterials = true, bool tryUnloadTextures = true) noexcept;
        bool isLoaded(std::string name) const noexcept;

        void dispose() noexcept;
        void log() const noexcept;

    private:
        std::shared_ptr<const Model> loadObjModel(std::string name, Path path) noexcept;

        std::unordered_map<std::string, std::shared_ptr<Model>> m_models;
    };
}