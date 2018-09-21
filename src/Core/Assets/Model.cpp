#include <Core/Assets/Model.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Assets/AssetManager.hpp>
#include <Core/Logger/Logger.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader/tiny_obj_loader.h>

using namespace ax;

AssetReference<Model> ModelManager::operator()(std::string name) const noexcept
{
    try
    {
        return m_models.at(name)->reference();
    }
    catch(std::out_of_range e)
    {
        Engine::interrupt("Failed to access model '" + name + "'");
    }
}
AssetReference<Model> ModelManager::load(std::string name, Path path) noexcept
{
    if(isLoaded(name))
    {
        Engine::logger().log("Failed to load model '" + name + "' because it already exists.", Logger::Warning);
        return AssetReference<Model>();
    }

    if(path.extension() == ".obj")
        return loadObjModel(name, path);

    return AssetReference<Model>();
}
bool ModelManager::unload(std::string name, bool tryUnloadMaterials, bool tryUnloadTextures) noexcept
{
    if(!isLoaded(name))
    {
        Engine::logger().log("Failed to unload model '" + name + "' because it does not exists.", Logger::Warning);
        return false;
    }

    Model* model = m_models.at(name)->get();

    for(auto it = model->meshes.begin(); it != model->meshes.end(); it++)
    {
        std::string meshName = it->get()->name;
        it->reset();
        Engine::assets().mesh.unload(meshName);
    }
    model->meshes.clear();
    for(auto it = model->materials.begin(); it != model->materials.end(); it++)
    {
        std::string materialName = it->get()->name;
        it->reset();
        Engine::assets().material.unload(materialName);
    }
    model->materials.clear();

    if(m_models.at(name)->referenceCount() > 0) return false;

    m_models.erase(name);

    return true;
}
bool ModelManager::isLoaded(std::string name) const noexcept
{
    return m_models.find(name) != m_models.end();
}

AssetReference<Model> ModelManager::loadObjModel(std::string name, Path path) noexcept
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string err;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path.c_str(), path.directory().c_str(), true);
    if(!ret)
    {
        Engine::logger().log("Failed to load model '" + name + "'", Logger::Warning);
        Engine::logger().log("TINYOBJ Error: " + err);
        return AssetReference<Model>();
    }

    //Loading materials
    for(const auto& material : materials)
    {
        if(!Engine::assets().material.isLoaded(material.name))
        {
            MaterialParameters data;

            //Diffuse Texture
            Path diffusePath = path.directory() + material.diffuse_texname;
            bool hasDiffuseTex = !diffusePath.filename().empty() &&
                (Engine::assets().texture.isLoaded(diffusePath.filename()) ||
                 Engine::assets().texture.load(diffusePath.filename(), diffusePath.path()));
            
            if(hasDiffuseTex)
                data.diffuseTexture = diffusePath.filename();  
            else
            {
                data.diffuseUniform.r = material.diffuse[0];
                data.diffuseUniform.g = material.diffuse[1];
                data.diffuseUniform.b = material.diffuse[2];
            }

            Engine::assets().material.load(material.name, data);
        } 
    }

    //Loading meshes
    std::unordered_map<int, std::vector<Vertex>> meshes;
    for(size_t s = 0; s < shapes.size(); s++)
    {
        size_t index_offset = 0;
        for(size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
        {
            int fv = shapes[s].mesh.num_face_vertices[f];
            int materialId =  shapes[s].mesh.material_ids[f];

            for(size_t v = 0; v < fv; v++)
            {
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

                Vertex vertex;
                vertex.position.x = attrib.vertices[3 * idx.vertex_index + 0];
                vertex.position.y = attrib.vertices[3 * idx.vertex_index + 1];
                vertex.position.z = attrib.vertices[3 * idx.vertex_index + 2];
                vertex.normal.x = attrib.vertices[3 * idx.normal_index + 0];
                vertex.normal.y = attrib.vertices[3 * idx.normal_index + 1];
                vertex.normal.z = attrib.vertices[3 * idx.normal_index + 2];
                vertex.uv.x = attrib.vertices[2 * idx.texcoord_index + 0];
                vertex.uv.y = attrib.vertices[2 * idx.texcoord_index + 1];
                vertex.color.x = attrib.colors[3 * idx.vertex_index + 0];
                vertex.color.y = attrib.colors[3 * idx.vertex_index + 1];
                vertex.color.z = attrib.colors[3 * idx.vertex_index + 2];

                meshes[materialId].push_back(vertex);
            }
            index_offset += fv;
        }
    }

    //Loading models
    m_models.emplace(name, std::make_shared<Model>());
    Model* model = m_models[name].get();
    model->name = name;

    for(auto it = meshes.begin(); it != meshes.end(); it++)
    {
        size_t i = std::distance(meshes.begin(), it);
        
        std::string meshName = name + "_" + std::to_string(i);
        Engine::assets().mesh.load(meshName, it->second, true);
        model->meshes.emplace_back(Engine::assets().mesh(meshName));

        if(it->first != -1)
        {
            std::string materialName = materials[it->first].name;
            model->materials.emplace_back(Engine::assets().material(materialName));
        }
        else
        {
            model->materials.emplace_back(AssetReference<Material>());
        }
    }

    return m_models.at(name);
}

void ModelManager::dispose() noexcept
{
    std::vector<std::string> keys;
    keys.reserve(m_models.size());
    for(auto it : m_models)
        keys.emplace_back(it.second->name);

    for(auto it : keys) unload(it, true, true);
}
void ModelManager::log() const noexcept
{
    Engine::logger().log("[    MODEL    ]", Logger::Info);
    
    for(auto it = m_models.begin(); it != m_models.end(); it++)
    {
        Engine::logger().log("- " + it->second.get()->name, Logger::Info);
    }
}