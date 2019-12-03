#pragma once

#include <core/export.hpp>
#include <core/utility/types.hpp>
#include <core/utility/reference.hpp>
#include <core/math/geometry/uv_sphere.hpp>
#include <core/scene/entity/entity.hpp>
#include <core/content/component/transform_component.hpp>
#include <core/content/asset/material_asset.hpp>
#include <core/renderer/scene/renderer_staticmesh.hpp>
#include <core/renderer/asset/renderer_mesh.hpp>

namespace ax
{
    class AXION_CORE_API uv_sphere_shape_component : public uv_sphere, public component
    {
    public:
        COMPONENT_IDENTIFIER("uv_sphere_shape")
        COMPONENT_REQUIREMENTS(transform_component)

        uv_sphere_shape_component(entity& entity, const json& json);
        uv_sphere_shape_component(entity& entity,
            float radius = 1.0f,
            unsigned slice = 30,
            unsigned stack = 30,
            bool smooth = true,
            float factor = 1.0f
        );
        ~uv_sphere_shape_component();

        void set_material(std::nullptr_t) noexcept;
        void set_material(const std::string& name) noexcept;
        void set_material(reference<material_asset> material) noexcept;

        void set_smooth(bool smooth) noexcept;
        void set_coordinate_factor(float factor) noexcept;

        void generate() noexcept;

        transform_component& transform;

    private:
        bool m_smooth = false;
        float m_coordinate_factor = 1.0f;

        renderer_staticmesh_handle m_staticmesh;
        renderer_mesh_handle m_mesh;
        reference<material_asset> m_material;
    };
}