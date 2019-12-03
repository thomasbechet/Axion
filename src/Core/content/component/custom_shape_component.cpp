#include <core/content/component/custom_shape_component.hpp>

using namespace ax;

custom_shape_component::custom_shape_component(entity& entity, const json& json) :
    transform(entity.get_component<transform_component>())
{

}
custom_shape_component::custom_shape_component(entity& entity) :
    transform(entity.get_component<transform_component>())
{

}
custom_shape_component::~custom_shape_component()
{

}