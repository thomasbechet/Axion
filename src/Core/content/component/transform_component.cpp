#include <core/content/component/transform_component.hpp>

#include <core/utility/json_utility.hpp>

using namespace ax;

transform_component::transform_component(entity& entity, const json& json) :
    transform_component(
        entity,
        json_utility::read_vector3f(json, "translation"),
        json_utility::read_quaternionf(json, "rotation"),
        json_utility::read_vector3f(json, "scale", vector3f(1, 1, 1))
    )
{
    auto childs = json.find("childs");
    if(childs != json.end())
    {
        for(auto& [key, item] : childs->items())
        {
            entity& entity = engine::scene().entity.create(key, item);
            entity.get_component<_transform_component>().attach_to(*this);
        }
    }
}
transform_component::transform_component(entity& entity, vector3f translation, quaternionf rotation, vector3f scale) :
    entity(entity)
{
    m_translation = translation;
    m_rotation = rotation;
    m_scale = scale;
}
transform_component::~transform_component()
{
    while(has_child()) first_child->detach();
    if(is_attached()) detach();
}

void transform_component::set_translation(float x, float y, float z) noexcept
{
    set_translation(_vector3f(x, y, z));
}
void transform_component::set_translation(const vector3f& translation) noexcept
{
    m_translation = translation;
    m_request_compute = true;
}
vector3f transform_component::get_translation() const noexcept
{
    return m_translation;
}
void transform_component::set_rotation(float angle, const vector3f& axis) noexcept
{
    set_rotation(_quaternionf(angle, axis));
}
void transform_component::set_rotation(const quaternionf& rotation) noexcept
{
    m_rotation = rotation;
    m_request_compute = true;
}
quaternionf transform_component::get_rotation() const noexcept
{
    return m_rotation;
}
void transform_component::set_scale(float x, float y, float z) noexcept
{
    set_scale(_vector3f(x, y, z));
}
void transform_component::set_scale(const vector3f& scale) noexcept
{
    m_scale = scale;
    m_request_compute = true;
}
vector3f transform_component::get_scale() const noexcept
{
    return m_scale;
}

void transform_component::rotate(float angle, vector3f axis) noexcept
{
    m_rotation *= quaternionf(angle, axis);
    m_request_compute = true;
}
void transform_component::translate(vector3f vec) noexcept
{
    m_translation += vec;
    m_request_compute = true;
}

vector3f transform_component::get_forward_vector() const noexcept
{
    return vector3f::normalize(m_rotation * vector3f::forward);
}
vector3f transform_component::get_backward_vector() const noexcept
{
    return vector3f::normalize(m_rotation * vector3f::backward);
}
ector3f transform_component::get_left_vector() const noexcept
{
    return vector3f::normalize(m_rotation * vector3f::left);
}
vector3f transform_component::get_right_vector() const noexcept
{
    return vector3f::normalize(m_rotation * vector3f::right);
}
vector3f transform_component::get_up_vector() const noexcept
{
    return vector3f::normalize(m_rotation * vector3f::up);
}
vector3f transform_component::get_down_vector() const noexcept
{
    return vector3f::normalize(m_rotation * vector3f::down);
}

void transform_component::attach_to(entity& entity) noexcept
{
    set_parent(&entity.get_component<transform_component>());
}
void transform_component::attach_to(transform_component& parent) noexcept
{
    set_parent(&parent);
}
void transform_component::detach() noexcept
{
    set_parent(nullptr);
}
bool transform_component::is_attached() const noexcept
{
    return parent != nullptr;
}
bool transform_component::has_child() const noexcept
{   
    return first_child != nullptr;
}

matrix4f transform_component::get_world_matrix() const noexcept
{
    return local_to_world();
}
matrix4f transform_component::get_matrix() const noexcept
{
    return local_to_parent();
}

void transform_component::set_parent(transform_component* new_parent) noexcept
{
    if(parent) //Remove from existing parent
    {
        if(prev_sibling) prev_sibling->next_sibling = next_sibling;
        else parent->first_child = next_sibling; //No previous, next become first

        if(next_sibling) next_sibling->prev_sibling = prev_sibling;

        prev_sibling = nullptr;
        next_sibling = nullptr;
        parent = nullptr;
    }

    parent = new_parent;

    if(parent) //Add to new parent
    {
        if(parent->first_child) parent->first_child->prev_sibling = this;
        next_sibling = parent->first_child;
        parent->first_child = this;
    }
}
matrix4f transform_component::local_to_world() const noexcept
{
    if(parent) 
        return parent->local_to_world() * local_to_parent();
    else 
        return local_to_parent();
}
matrix4f transform_component::local_to_parent() const noexcept
{
    if(m_request_compute)
    {
        m_transform = matrix4f::translate(m_translation) * quaternionf::to_matrix(m_rotation) * matrix4f::scale(m_scale);
        m_request_compute = false;
    }

    return m_transform;
}