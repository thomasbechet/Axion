#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>

namespace ax
{
    class AXION_CORE_API MeshManager
    {
    public:
        AssetReference<Mesh> operator()(std::string name) const noexcept;
        AssetReference<Mesh> create(std::string name, const std::vector<Vertex>& vertices, bool computeTangent = false, bool computeNormal = false) noexcept;
        bool destroy(std::string name) noexcept;
        bool exists(std::string name) const noexcept;

        void dispose() noexcept;
        void log() const noexcept;

    private:
        std::unordered_map<std::string, std::unique_ptr<AssetHolder<Mesh>>> m_meshes;
    };
}