#pragma once

/////////////
//HEADERS
/////////////
#include <Core/Export.hpp>
#include <Core/Assets/Texture.hpp>
#include <Core/Assets/Mesh.hpp>
#include <Core/Assets/Material.hpp>
#include <Core/Assets/Model.hpp>
#include <Core/Assets/Shader.hpp>

#include <string>
#include <memory>
#include <vector>

namespace ax
{
    struct AXION_CORE_API Package
    {
        std::string name;

        std::vector<std::shared_ptr<const Texture>> textures;
        std::vector<std::shared_ptr<const Mesh>> meshes;
        std::vector<std::shared_ptr<const Material>> materials;
        std::vector<std::shared_ptr<const Model>> models;
        std::vector<std::shared_ptr<const Shader>> shaders;
    };

    class AXION_CORE_API PackageManager
    {
    public:
        std::shared_ptr<const Package> operator()(std::string name) const noexcept;
        std::shared_ptr<const Package> load(Path path) noexcept;
        bool unload(std::string name) noexcept;
        bool isLoaded(std::string name) const noexcept;

        void dispose() noexcept;
        void log() const noexcept;

    private:
        std::unordered_map<std::string, std::shared_ptr<Package>> m_packages;
    };
}