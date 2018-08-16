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

    std::cout << "load model " << name << std::endl; 

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string err;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path.c_str(), path.directory().c_str());
    if(!ret)
    {
        Game::logger().log("Failed to load model '" + name + "'", Logger::Warning);
        Game::logger().log("TINYOBJ Error: " + err);
        return false;
    }

    m_models.emplace(name, std::make_shared<Model>());
    Model* newModel = m_models[name].get();

    for(const auto& material : materials)
    {
        std::string materialName = name + "_" + material.name;
        
    }

    for(const auto& shape : shapes)
    {
        std::cout << "new shape !" << std::endl;

        std::vector<Vertex> vertices;
        for(const auto& index : shape.mesh.indices)
        {
            Vertex vertex;

            vertex.position.x = attrib.vertices[3 * index.vertex_index + 0];
            vertex.position.y = attrib.vertices[3 * index.vertex_index + 1];
            vertex.position.z = attrib.vertices[3 * index.vertex_index + 2];
   
            vertex.uv.x = attrib.texcoords[2 * index.texcoord_index + 0];
            vertex.uv.y = attrib.texcoords[2 * index.texcoord_index + 1];

            //vertex.normal.x = attrib.normals[3 * index.normal_index + 0];
            //vertex.normal.y = attrib.normals[3 * index.normal_index + 1];
            //vertex.normal.z = attrib.normals[3 * index.normal_index + 2]; 

            vertex.color.x = attrib.colors[3 * index.vertex_index + 0];
            vertex.color.y = attrib.colors[3 * index.vertex_index + 1];
            vertex.color.z = attrib.colors[3 * index.vertex_index + 2];

            vertices.push_back(vertex);
        }

        //loadMesh(shape.name, vertices);
    }

    return true;
}
bool AssetManager::unloadModel(std::string name) noexcept
{
    if(!modelExists(name))
    {
        Game::logger().log("Failed to unload model '" + name + "' because it does not exists.", Logger::Warning);
        return false;
    }

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
