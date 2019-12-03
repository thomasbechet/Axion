#pragma once

#include <core/export.hpp>
#include <core/utility/types.hpp>
#include <core/utility/reference.hpp>
#include <core/math/geometry/rectangle.hpp>
#include <core/scene/entity/entity.hpp>
#include <core/content/component/transform_component.hpp>
#include <core/content/asset/material_asset.hpp>
#include <core/renderer/scene/renderer_staticmesh.hpp>
#include <core/renderer/asset/renderer_mesh.hpp>

namespace ax
{
    class AXION_CORE_API rectangle_shape_component : public rectangle, public component
    {
    public:
        COMPONENT_IDENTIFIER("rectangle_shape")
        COMPONENT_REQUIREMENTS(transform_component)
        
        rectangle_shape_component(entity& entity, const json& json);
        rectangle_shape_component(entity& entity,
            float xMin = -0.5f, float xMax = 0.5f,
            float yMin = -0.5f, float yMax = 0.5f,
            float zMin = -0.5f, float zMax = 0.5f,
            bool smooth = true,
            float factor = 1.0f
        );
        ~rectangle_shape_component();

        void set_material(std::nullptr_t) noexcept;
        void set_material(const std::string& name) noexcept;
        void set_material(reference<material_asset> material) noexcept;

        void set_coordinate_factor(float factor) noexcept;

        void generate() noexcept;

        transform_component& transform;

    private:
        float m_coordinate_factor = 1.0f;

        renderer_staticmesh_handle m_staticmesh;
        renderer_mesh_handle m_mesh;
        reference<material_asset> m_material;
    };
}