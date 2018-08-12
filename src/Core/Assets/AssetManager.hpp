#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>
#include <Core/Utility/Path.hpp>
#include <Core/Assets/Texture.hpp>
#include <Core/Assets/Mesh.hpp>
#include <Core/Assets/Material.hpp>
#include <Core/Assets/Model.hpp>
#include <Core/Assets/Package.hpp>

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

namespace ax
{
    class AXION_CORE_API AssetManager
    {
    public:
        ~AssetManager();

        void logInfo() const noexcept;

        bool loadPackage(Path path) noexcept;
        bool unloadPackage(std::string name) noexcept;
        bool packageExists(std::string name) noexcept;
        std::shared_ptr<const Package> getPackage(std::string name) noexcept;

        bool loadTexture(std::string name, Path path) noexcept;
        bool unloadTexture(std::string name) noexcept;
        bool textureExists(std::string name) noexcept;
        std::shared_ptr<const Texture> getTexture(std::string name) noexcept;

        bool loadMesh(std::string name, MeshData& mesh) noexcept;
        bool unloadMesh(std::string name) noexcept;
        bool meshExists(std::string name) noexcept;
        std::shared_ptr<const Mesh> getMesh(std::string name) noexcept;

        bool loadMaterial(std::string name, MaterialData& material) noexcept;
        bool unloadMaterial(std::string name) noexcept;
        bool materialExists(std::string name) noexcept;
        std::shared_ptr<const Material> getMaterial(std::string name) noexcept;

        bool loadModel(std::string name, Path path) noexcept;
        bool unloadModel(std::string name) noexcept;
        bool modelExists(std::string name) noexcept;
        std::shared_ptr<const Model> getModel(std::string name) noexcept;

    private:
        std::unordered_map<std::string, std::shared_ptr<Texture>> m_textures;
        std::unordered_map<std::string, std::shared_ptr<Mesh>> m_meshes;
        std::unordered_map<std::string, std::shared_ptr<Material>> m_materials;
        std::unordered_map<std::string, std::shared_ptr<Model>> m_models;
        std::unordered_map<std::string, std::shared_ptr<Package>> m_packages;
    };
}