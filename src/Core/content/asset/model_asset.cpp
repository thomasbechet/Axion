#include <core/content/asset/model_asset.hpp>

#include <core/asset/asset_module.ipp>
#include <core/asset/json_attributes.hpp>
#include <core/utility/json.hpp>
#include <core/utility/json_utility.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader/tiny_obj_loader.h>

using namespace ax;

model_asset::model_asset(const std::string& name, const parameters& parameters) :
    asset(name, identifier),
    m_parameters(parameters)
{

}

const std::vector<reference<mesh_asset>>& model_asset::get_meshes() const noexcept
{
    return m_meshes;
}
const std::vector<reference<material_asset>>& model_asset::get_materials() const noexcept
{
    return m_materials;
}

bool model_asset::on_load() noexcept
{
    if(!m_parameters.source.empty())
    {
        return load_from_source(m_parameters.source);
    }
    else if(!m_parameters.json.is_null())
    {
        try
        {
            Path source = m_parameters.json[json_attributes::source].get<std::string>();
            if(source.extension() == ".obj")
            {
                return load_obj_model(source);
            }
            else
            {
                log_load_error("_unknown extension file '" + source.extension() + "'");
                return false;
            }
        }
        catch(const std::exception& e)
        {
            log_load_error("_loading <" + model_asset::identifier + "> without '" + json_attributes::source + "' attribute");
            return false;
        }
    }

    log_load_error("_loading <" + model_asset::identifier + "> without inputs parameters");
    return false;
}
bool model_asset::on_validate() noexcept
{
    for(auto& it : m_dummy_models)
    {
        m_meshes.emplace_back(engine::asset().get<mesh_asset>(it.first));
        m_materials.emplace_back(engine::asset().get<material_asset>(it.second));
    }

    return true;
}
bool model_asset::on_unload() noexcept
{
    if(m_parameters.try_destroy_meshes)
    {
        for(auto it = m_meshes.begin(); it != m_meshes.end(); it++)
        {
            std::string mesh_name = it->get()->get_name();
            it->reset();
            Engine::asset().unload<mesh_asset>(mesh_name);
        }
    }
    m_meshes.clear();
    if(m_parameters.try_destroy_materials)
    {
        for(auto& it : m_materials)
        {
            std::string material_name = it.get()->get_name();
            it.reset();
            Engine::asset().unload<material_asset>(material_name);            
        }
    }
    m_materials.clear();

    return true;
}

bool model_asset::load_from_source(const path& path) noexcept
{
    if(m_parameters.source.extension() == ".obj")
    {
        return load_obj_model(m_parameters.source);
    }
    else if(m_parameters.source.extension() == ".json")
    {
        if(json_utility::parse_file(m_parameters.source, m_parameters.json))
            return load_from_json(m_parameters.json);
        else
            return false;
    }
    else
    {
        log_load_error("Unknown extension file '" + m_parameters.source.extension() + "'");
        return false;
    }
}
bool model_asset::load_from_json(const json& json) noexcept
{
    return false;
}
bool model_asset::load_obj_model(const path& path) noexcept
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string err;
    bool ret = tinyobj::load_obj(&attrib, &shapes, &materials, &err, path.c_str(), path.directory().c_str(), true);
    if(!ret)
    {
        log_load_error("tinyobj Error: " + err);
        return false;
    }

    //Loading materials
    for(const auto& material : materials)
    {
        if(!_engine::asset().exists<material_asset>(material.name))
        {
            material_asset::parameters material_parameters;

            //Diffuse Texture
            path diffuse_path = path.directory() + material.diffuse_texname;
            if(!diffuse_path.filename().empty())
            {
                if(!engine::asset().exists<texture_asset>(diffuse_path.filename()))
                {
                    texture_asset::parameters texture_parameters;
                    texture_parameters.source = diffuse_path;
                    if(m_parameters.async_loading)
                        engine::asset().loadAsync<texture_asset>(diffuse_path.filename(), texture_parameters);
                    else
                        engine::asset().load<texture_asset>(diffuse_path.filename(), texture_parameters);
                }
                material_parameters.diffuse_texture = diffuse_path.filename();
            }
            else
            {
                material_parameters.diffuse_color.r = material.diffuse[0];
                material_parameters.diffuse_color.g = material.diffuse[1];
                material_parameters.diffuse_color.b = material.diffuse[2];
            }

            //Normal Texture
            path normal_path = path.directory() + material.normal_texname;
            path bump_path = path.directory() + material.bump_texname;
            if(!normal_path.filename().empty())
            {
                if(!engine::asset().exists<texture_asset>(normal_path.filename()))
                {
                    texture_asset::_parameters texture_parameters;
                    texture_parameters.source = normal_path;
                    if(m_parameters.async_loading)
                        engine::asset().loadAsync<texture_asset>(normal_path.filename(), texture_parameters);
                    else
                        engine::asset().load<texture_asset>(normal_path.filename(), texture_parameters);
                }
                material_parameters.normal_texture = normal_path.filename();
                material_parameters.is_bump_texture = false;
            }
            else if(!bump_path.filename().empty())
            {
                if(!engine::asset().exists<texture_asset>(bump_path.filename()))
                {
                    texture_asset::parameters texture_parameters;
                    texture_parameters.source = bump_path;
                    if(m_parameters.async_loading)
                        engine::asset().loadAsync<texture_asset>(bump_path.filename(), texture_parameters);
                    else
                        engine::asset().load<texture_asset>(bump_path.filename(), texture_parameters);
                }
                material_parameters.normal_texture = bump_path.filename();
                material_parameters.is_bump_texture = true;
            }

            //Specular
            path specular_path = path.directory() + material.specular_texname;
            if(!specular_path.filename().empty())
            {
                if(!engine::asset().exists<texture_asset>(specular_path.filename()))
                {
                    texture_asset::parameters texture_parameters;
                    texture_parameters.source = specular_path;
                    if(m_parameters.async_loading)
                        Engine::asset().loadAsync<texture_asset>(specular_path.filename(), texture_parameters);
                    else
                        Engine::asset().load<texture_asset>(specular_path.filename(), texture_parameters);
                }
                material_parameters.specular_texture = specular_path.filename();
            }
            else
            {
                material_parameters.specular_uniform = material.shininess;
            }

            //Load material as assets
            if(m_parameters.async_loading)
                engine::asset().load_async<material_asset>(material.name, material_parameters);
            else
                engine::asset().load<material_asset>(material.name, material_parameters);
        } 
    }

    //Loading meshes
    std::unordered_map<int, std::vector<vertex>> meshes;
    for(size_t s = 0; s < shapes.size(); s++)
    {
        size_t index_offset = 0;
        for(size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
        {
            int fv = shapes[s].mesh.num_face_vertices[f];
            int material_id =  shapes[s].mesh.material_ids[f];

            for(size_t v = 0; v < fv; v++)
            {
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

                vertex vertex;
                vertex.position.x = attrib.vertices[3 * idx.vertex_index + 0];
                vertex.position.y = attrib.vertices[3 * idx.vertex_index + 1];
                vertex.position.z = attrib.vertices[3 * idx.vertex_index + 2];
                
                if(!attrib.texcoords.empty())
                {
                    vertex.uv.x = attrib.texcoords[2 * idx.texcoord_index + 0];
                    vertex.uv.y = attrib.texcoords[2 * idx.texcoord_index + 1];
                }

                if(!attrib.normals.empty())
                {
                    vertex.normal.x = attrib.normals[3 * idx.normal_index + 0];
                    vertex.normal.y = attrib.normals[3 * idx.normal_index + 1];
                    vertex.normal.z = attrib.normals[3 * idx.normal_index + 2];                    
                }

                vertex.color.r = attrib.colors[3 * idx.vertex_index + 0];
                vertex.color.g = attrib.colors[3 * idx.vertex_index + 1];
                vertex.color.b = attrib.colors[3 * idx.vertex_index + 2];

                meshes[material_id].push_back(vertex);
            }

            index_offset += fv;
        }
    }

    //Loading models
    for(auto it = meshes.begin(); it != meshes.end(); it++)
    {
        size_t i = std::distance(meshes.begin(), it);
        
        std::string mesh_name = get_name() + "_" + std::to_string(i);
        mesh_asset::parameters mesh_parameters;
        mesh_parameters.vertices = it->second;
        mesh_parameters.compute_tangent = true;
        mesh_parameters.compute_normal = attrib.normals.empty();
        if(m_parameters.async_loading)
            engine::asset().loadAsync<mesh_asset>(mesh_name, mesh_parameters);
        else
            engine::asset().load<mesh_asset>(mesh_name, mesh_parameters);

        if(it->first != -1)
        {
            std::string material_name = materials[it->first].name;
            m_dummyModels.emplace_back(std::make_pair(mesh_name, material_name));
        }
        else
        {
            m_dummyModels.emplace_back(std::make_pair(mesh_name, material_asset::default));
        }
    }

    return true;
}