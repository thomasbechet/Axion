#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>
#include <Core/Asset/Mesh.hpp>

namespace ax
{
    class AXION_CORE_API MeshManager
    {
    public:
        AssetReference<Mesh> operator()(std::string name) const noexcept;
        AssetReference<Mesh> loadFromJson(std::string name, const std::string& json) noexcept;
        AssetReference<Mesh> loadFromFile(std::string name, Path file) noexcept;
        AssetReference<Mesh> loadFromMemory(std::string name, const std::vector<Vertex>& vertices, bool computeTangent = false, bool computeNormal = false) noexcept;
        bool unload(std::string name) noexcept;
        bool exists(std::string name) const noexcept;

        void dispose() noexcept;
        void log() const noexcept;

    private:
        std::unordered_map<std::string, std::unique_ptr<AssetHolder<Mesh>>> m_meshes;
    };
}