#include <core/content/component/model_component.hpp>

#include <core/asset/asset_module.ipp>
#include <core/renderer/renderer_module.hpp>
#include <core/utility/json_utility.hpp>

using namespace ax;

model_component::_model_component(entity& entity, const json& json) :
    transform(entity.get_component<transform_component>())
{
    std::string model = json_utility::read_string(json, "model");
    if(!model.empty())
        set_model(model);
}
model_component::model_component(entity& entity) :
    transform(entity.get_component<transform_component>())
{

}
model_component::~model_component()
{
    set_model(nullptr);
}

void model_component::set_model(std::nullptr_t) noexcept
{
    for(auto& reference : m_elements)
    {
        engine::renderer().destroy_staticmesh(std::get<renderer_staticmesh_handle>(reference));
        std::get<reference<mesh_asset>>(reference).reset();
        std::get<reference<material_asset>>(reference).reset();
    }

    m_elements.clear();
}
void model_component::set_model(const std::string& name) noexcept
{
    set_model(_engine::asset().get<_model_asset>(name));
}
void model_component::set_model(reference<model_asset> model) noexcept
{
    set_model(nullptr);

    const std::vector<reference<mesh_asset>>& meshes = model->get_meshes();
    const std::vector<reference<material_asset>>& materials = model->get_materials();

    m_elements.reserve(meshes.size());

    for(size_t it = 0; it < meshes.size(); it++)
    {
        renderer_staticmesh_handle staticmesh = engine::renderer().create_staticmesh();
        staticmesh->set_transform(&transform);
        staticmesh->set_mesh(meshes[it]->get_handle());
        staticmesh->set_material(materials[it]->get_handle());

        m_elements.emplace_back(std::tuple<reference<mesh_asset>, reference<material_asset>, renderer_staticmesh_handle>(
            meshes[it], materials[it], staticmesh
        ));
    }
}
void model_component::set_model(reference<mesh_asset> mesh) noexcept
{   
    set_model(nullptr);

    reference<material_asset> material = engine::asset().get<material_asset>(material_asset::_default);

    renderer_staticmesh_handle staticmesh = engine::renderer().create_staticmesh();
    staticmesh->set_transform(&transform);
    staticmesh->set_mesh(mesh->get_handle());
    staticmesh->set_material(material->get_handle());

    m_elements.emplace_back(std::tuple<reference<mesh_asset>, reference<material_asset>, renderer_staticmesh_handle>(
        mesh, material, staticmesh
    ));
}

void model_component::set_material(std::nullptr_t ptr, Id component) noexcept
{
    std::tuple<reference<mesh_asset>, reference<_material_asset>, renderer_staticmesh_handle>& reference = m_elements.at(component);

    std::get<reference<material_asset>>(reference).reset();

    std::get<renderer_staticmesh_handle>(reference)->setMaterial(nullptr);
}
void model_component::set_material(const std::string& name, id component) noexcept
{
    set_material(engine::asset().get<_material_asset>(name), component);
}
void model_component::setMaterial(reference<material_asset> material, id component) noexcept
{
    if(material)
    {
        std::tuple<reference<mesh_asset>, reference<material_asset>, renderer_staticmesh_handle>& reference = m_elements.at(component);

        std::get<reference<material_asset>>(reference).reset();
        std::get<reference<material_asset>>(reference) = material;

        std::get<renderer_staticmesh_handle>(reference)->setMaterial(std::get<reference<material_asset>>(reference)->getHandle());
    }
    else
    {
        set_material(nullptr, component);
    }   
}