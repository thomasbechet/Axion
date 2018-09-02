#include <Core/Assets/AssetManager.hpp>

#include <Core/Context/Game.hpp>
#include <Core/Logger/Logger.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader/tiny_obj_loader.h>

using namespace ax;

bool AssetManager::loadModel(std::string name, Path path) noexcept
{
    if(modelExists(name))
    {
        Game::logger().log("Failed to load model '" + name + "' because it already exists.", Logger::Warning);
        return false;
    }

    if(path.extension() == ".obj")
        return loadObjModel(name, path);

    return false;
}
bool AssetManager::unloadModel(std::string name) noexcept
{
    if(!modelExists(name))
    {
        Game::logger().log("Failed to unload model '" + name + "' because it does not exists.", Logger::Warning);
        return false;
    }

    Model* model = m_models.at(name).get();

    for(auto it = model->meshes.begin(); it != model->meshes.end(); it++)
    {
        std::string meshName = it->get()->name;
        it->reset();
        unloadMesh(meshName);
    }
    model->meshes.clear();
    for(auto it = model->materials.begin(); it != model->materials.end(); it++)
    {
        std::string materialName = it->get()->name;
        it->reset();
        unloadMaterial(materialName);
    }
    model->materials.clear();

    if(m_models.at(name).use_count() != 1) return false;

    m_models.erase(name);

    return true;
}
bool AssetManager::modelExists(std::string name) noexcept
{
    return m_models.find(name) != m_models.end();
}
std::shared_ptr<const Model> AssetManager::getModel(std::string name) noexcept
{
    try
    {
        return std::const_pointer_cast<const Model>(m_models.at(name));
    }
    catch(std::out_of_range e)
    {
        Game::interrupt("Failed to access model '" + name + "'");
    }   
}

bool AssetManager::loadObjModel(std::string name, Path path) noexcept
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string err;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path.c_str(), path.directory().c_str(), true);
    if(!ret)
    {
        Game::logger().log("Failed to load model '" + name + "'", Logger::Warning);
        Game::logger().log("TINYOBJ Error: " + err);
        return false;
    }

    //Loading materials
    for(const auto& material : materials)
    {
        if(!materialExists(material.name))
        {
            MaterialData data;

            //Diffuse Texture
            Path diffusePath = path.directory() + material.diffuse_texname;
            bool hasDiffuseTex = !diffusePath.filename().empty() &&
                (textureExists(diffusePath.filename()) ||
                 loadTexture(diffusePath.filename(), diffusePath.path()));
            
            if(hasDiffuseTex)
                data.diffuseTexture = diffusePath.filename();  
            else
            {
                data.diffuseUniform.r = material.diffuse[0];
                data.diffuseUniform.g = material.diffuse[1];
                data.diffuseUniform.b = material.diffuse[2];
            }

            loadMaterial(material.name, data);
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
    Model* newModel = m_models[name].get();
    newModel->name = name;

    for(auto it = meshes.begin(); it != meshes.end(); it++)
    {
        size_t i = std::distance(meshes.begin(), it);
        
        std::string meshName = name + "_" + std::to_string(i);
        loadMesh(meshName, it->second);
        newModel->meshes.emplace_back(getMesh(meshName));

        if(it->first != -1)
        {
            std::string materialName = materials[it->first].name;
            newModel->materials.emplace_back(getMaterial(materialName));
        }
        else
        {
            newModel->materials.emplace_back(nullptr);
        }
    }

    return true;
}