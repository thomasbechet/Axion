#pragma once

/////////////
//HEADERS
/////////////
#include <Core/Export.hpp>
#include <Core/Math/Vector.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Utility/Path.hpp>
#include <Core/Utility/Vertex.hpp>
#include <Core/Assets/AssetReference.hpp>

#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

namespace ax
{
    struct AXION_CORE_API Mesh
    {
        std::string name;

        std::vector<Vertex> vertices;
        
        Id handle;
    };

    class AXION_CORE_API MeshManager
    {
    public:
        AssetReference<Mesh> operator()(std::string name) const noexcept;
        AssetReference<Mesh> load(std::string name, const std::vector<Vertex>& vertices, bool computeTangent = false) noexcept;
        bool unload(std::string name) noexcept;
        bool isLoaded(std::string name) const noexcept;

        void dispose() noexcept;
        void log() const noexcept;

    private:
        std::unordered_map<std::string, std::unique_ptr<AssetHolder<Mesh>>> m_meshes;
    };
}