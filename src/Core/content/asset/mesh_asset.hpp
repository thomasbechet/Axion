#pragma once

#include <core/export.hpp>
#include <core/math/vector.hpp>
#include <core/utility/path.hpp>
#include <core/utility/json.hpp>
#include <core/utility/macro.hpp>
#include <core/math/geometry/vertex.hpp>
#include <core/asset/esset.hpp>
#include <core/renderer/asset/renderer_mesh.hpp>

#include <string>
#include <vector>

namespace ax
{
    class AXION_CORE_API mesh_asset : public asset
    {
    public:
        struct parameters
        {
            path source;
            json json;
            std::vector<vertex> vertices;
            bool compute_tangent = false;
            bool compute_normal = false;
        };

    public:
        ASSET_IDENTIFIER("mesh")
        
        mesh_asset(const std::string& name, const parameters& parameters);

        const std::vector<vertex>& get_vertices() const noexcept;
        renderer_mesh_handle get_handle() const noexcept;

    private:
        bool on_load() noexcept override;
        bool on_validate() noexcept override;
        bool on_unload() noexcept override;

    private:
        bool load_from_source(const path& path) noexcept;
        bool load_from_json(const json& json) noexcept;
        void process_geometry() noexcept;

    private:
        parameters m_parameters;
        renderer_mesh_handle m_handle;
    };
}