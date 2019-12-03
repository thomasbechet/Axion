#pragma once

#include <core/export.hpp>
#include <core/utility/types.hpp>
#include <core/math/geometry/shape.hpp>
#include <core/scene/entity/entity.hpp>
#include <core/content/component/transform_component.hpp>

namespace ax
{
    class AXION_CORE_API custom_shape_component : public component
    {
    public:
        COMPONENT_IDENTIFIER("custom_shape")
        COMPONENT_REQUIREMENTS(transform_component)
        
        custom_shape_component(entity& entity, const json& json);
        custom_shape_component(entity& entity);
        ~custom_shape_component();

        void set_vertices(const std::vector<vertex>& points) noexcept;
        void set_vertices(const std::vector<vector3f>& points) noexcept;
        const std::vector<vertex>& get_vertices() const noexcept;

        transform_component& transform;

    private:
        //Id m_handle;
        std::vector<vertex> m_vertices;
    };
}