#pragma once

/////////////
//HEADERS
/////////////
#include <Core/Export.hpp>
#include <Core/Math/Vector.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Utility/Path.hpp>
#include <Core/Utility/Vertex.hpp>

#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

namespace ax
{
    struct AXION_CORE_API Mesh
    {
        std::string name;

        std::vector<Vector3f> positions;
        std::vector<Vector2f> uvs;
        std::vector<Vector3f> normals;
        std::vector<Vector3f> tangents;
        std::vector<Vector3f> bitangents;
        std::vector<Vector3f> colors;
        size_t vertex_count;
        
        Id handle;
    };

    class AXION_CORE_API MeshManager
    {
    public:
        std::shared_ptr<const Mesh> operator()(std::string name) const noexcept;
        std::shared_ptr<const Mesh> load(std::string name, const std::vector<Vertex>& vertices) noexcept;
        bool unload(std::string name) noexcept;
        bool isLoaded(std::string name) const noexcept;

        void dispose() noexcept;
        void log() const noexcept;

    private:
        std::unordered_map<std::string, std::shared_ptr<Mesh>> m_meshes;
    };
}