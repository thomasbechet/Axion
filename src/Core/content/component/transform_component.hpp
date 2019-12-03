#pragma once

#include <core/export.hpp>
#include <core/scene/entity/entity.ipp>
#include <core/scene/component/component.hpp>
#include <core/math/vector.hpp>
#include <core/math/quaternion.hpp>
#include <core/utility/json.hpp>
#include <core/utility/macro.hpp>

namespace ax
{
    class AXION_CORE_API transform_component : public component
    {
    public:
        COMPONENT_IDENTIFIER("transform")
        COMPONENT_REQUIREMENTS()
        
        transform_component(entity& entity, const json& json);
        transform_component(
            entity& entity,
            vector3f position = vector3f(0.0f, 0.0f, 0.0f), 
            quaternionf rotation = quaternionf(), 
            vector3f scale = vector3f(1.0f, 1.0f, 1.0f)
        );
        ~transform_component();

        void set_translation(float x = 0.0f, float y = 0.0f, float z = 0.0f) noexcept;
        void set_translation(const vector3f& position) noexcept;
        vector3f get_translation() const noexcept;
        void set_rotation(float angle = 0.0f, const vector3f& axis = vector3f(0.0f, 1.0f, 0.0f)) noexcept;
        void set_rotation(const quaternionf& rotation) noexcept;
        quaternionf get_rotation() const noexcept;
        void set_scale(float x = 1.0f, float y = 1.0f, float z = 1.0f) noexcept;
        void set_scale(const vector3f& scale) noexcept;
        vector3f get_scale() const noexcept;

        void rotate(float angle, vector3f axis) noexcept;
        void translate(vector3f vec) noexcept;

        vector3f get_forward_vector() const noexcept;
        vector3f get_backward_vector() const noexcept;
        vector3f get_left_vector() const noexcept;
        vector3f get_right_vector() const noexcept;
        vector3f get_up_vector() const noexcept;
        vector3f get_down_vector() const noexcept;

        void attach_to(entity& entity) noexcept;
        void attachTo(transform_component& new_parent) noexcept;
        void detach() noexcept;
        bool is_attached() const noexcept;
        bool has_child() const noexcept;

        matrix4f get_world_matrix() const noexcept;
        matrix4f get_matrix() const noexcept;

        entity& entity;

    private:
        void setParent(transform_component* new_parent) noexcept;
        matrix4f local_to_world() const noexcept;
        matrix4f local_to_parent() const noexcept;

        vector3f m_translation = vector3f(0.0f, 0.0f, 0.0f);
        quaternionf m_rotation = quaternionf(0.0f, vector3f(0.0f, 1.0f, 0.0f));
        vector3f m_scale = vector3f(1.0f, 1.0f, 1.0f);
 
        mutable matrix4f m_transform;
        mutable bool m_request_compute = true;

        transform_component* parent = nullptr;
        transform_component* first_child = nullptr;
        transform_component* next_sibling = nullptr;
        transform_component* prev_sibling = nullptr;
    };
}