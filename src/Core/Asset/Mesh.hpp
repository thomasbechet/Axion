#pragma once

#include <Core/Export.hpp>
#include <Core/Math/Vector.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Utility/Path.hpp>
#include <Core/Math/Geometry/Vertex.hpp>
#include <Core/Asset/AssetReference.hpp>

#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

namespace ax
{
    class AXION_CORE_API Mesh
    {
    public:
        Mesh();
        Mesh(std::string name);
        ~Mesh();

        bool loadFromFile(Path file) noexcept;
        bool loadFromJson(const std::string& json) noexcept;
        bool loadFromMemory(const std::vector<Vertex>& vertices, bool computeTangent = false, bool computeNormal = false) noexcept;
        bool unload() noexcept;
        bool isLoaded() const noexcept;

        std::string getName() const noexcept;

        const std::vector<Vertex>& getVertices() const noexcept;

        Id getHandle() const noexcept;

    private:
        std::string m_name;

        bool m_isLoaded = false;

        std::vector<Vertex> m_vertices;
        
        Id m_handle;
    };
}