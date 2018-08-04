#include <Core/Assets/AssetManager.hpp>

#include <Core/Context/Game.hpp>
#include <Core/Logger/Logger.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader/tiny_obj_loader.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>

using namespace ax;

AssetManager::~AssetManager()
{
    for(auto it : m_packages) unloadPackage(it.first);
    for(auto it : m_models) unloadModel(it.first);
    for(auto it : m_materials) unloadMaterial(it.first);
    for(auto it : m_textures) unloadTexture(it.first);
    for(auto it : m_meshes) unloadMesh(it.first);
}

bool AssetManager::loadPackage(Path path) noexcept
{
    rapidxml::file<> file(path.c_str());
    rapidxml::xml_document<> doc;
    try
    {
        doc.parse<0>(file.data());
    }
    catch(rapidxml::parse_error& e)
    {   
        Game::logger().log("Failed to parse package file " + path.path(), Logger::Warning);
        return false;
    }
    
    rapidxml::xml_node<>* package_node = doc.first_node("package");
    if(!package_node)
    {
        Game::logger().log("Failed to load package " + path.path() + " because it does not contain 'package' node", Logger::Warning);
        return false;
    }
    
    std::string name = path.filename();
    if(package_node->first_attribute("name"))
        name = package_node->first_attribute("name")->value();

    Path directory = "";
    if(package_node->first_attribute("directory")) 
        directory = Path(package_node->first_attribute("directory")->value());

    if(packageExists(name))
    {
        Game::logger().log("Failed to load package '" + name + "' because it already exists.", Logger::Warning);
        return false;
    }

    for(rapidxml::xml_node<>* texture_node = package_node->first_node("texture"); texture_node; texture_node = texture_node->next_sibling())
    {
        Path texture_path = directory + texture_node->value();
        std::string texture_name = texture_path.filename();
        if(texture_node->first_attribute("name"))
            texture_name = texture_node->first_attribute("name")->value();

        if(loadTexture(texture_name, texture_path))
        {
            
        }
    }

    m_packages[name] = std::make_shared<Package>();
    Package* package = m_packages[name].get();    

    return true;
}
bool AssetManager::unloadPackage(std::string name) noexcept
{
    if(!packageExists(name))
    {
        Game::logger().log("Failed to unload package '" + name + "' because it does not exists.", Logger::Warning);
        return false;
    }

    //m_packages.erase(name);

    return false;
}
bool AssetManager::packageExists(std::string name) noexcept
{
    return m_packages.find(name) != m_packages.end();
}
std::shared_ptr<const Package> AssetManager::getPackage(std::string name) noexcept
{
    try
    {
        return std::const_pointer_cast<const Package>(m_packages.at(name));
    }
    catch(std::out_of_range e)
    {
        Game::interrupt("Failed to access package '" + name + "'");
    }
}

bool AssetManager::loadTexture(std::string name, Path path) noexcept
{
    if(textureExists(name))
    {
        Game::logger().log("Failed to load texture '" + name + "' because it already exists.", Logger::Warning);
        return false;
    }

    int width, height, bpp;
    Byte* data = stbi_load(path.c_str(), &width, &height, &bpp, 0);
    if(data != nullptr)
    {
        m_textures[name] = std::make_shared<Texture>();
        Texture* texture = m_textures[name].get();

        texture->data = data;
        texture->size.x = (unsigned)width;
        texture->size.y = (unsigned)height;

        if(bpp == 3)
            texture->format = TextureFormat::RGB;
        else if(bpp == 4)
            texture->format = TextureFormat::RGBA;
    }
    else
    {
        Game::logger().log("Failed to load texture '" + path.path() + "'", Logger::Warning);
        return false;
    }

    return true;
}
bool AssetManager::unloadTexture(std::string name) noexcept
{
    if(!textureExists(name))
    {
        Game::logger().log("Failed to unload texture '" + name + "' because it does not exists.", Logger::Warning);
        return false;
    }

    stbi_image_free(m_textures[name]->data);
    m_textures.erase(name);

    return true;
}
bool AssetManager::textureExists(std::string name) noexcept
{
    return m_textures.find(name) != m_textures.end();
}
std::shared_ptr<const Texture> AssetManager::getTexture(std::string name) noexcept
{
    try
    {
        return std::const_pointer_cast<const Texture>(m_textures.at(name));
    }
    catch(std::out_of_range e)
    {
        Game::interrupt("Failed to access texture '" + name + "'");
    }   
}

bool AssetManager::loadMesh(std::string name, MeshData& mesh) noexcept
{
    if(meshExists(name))
    {
        Game::logger().log("Failed to load mesh '" + name + "' because it already exists.", Logger::Warning);
        return false;
    }

    m_meshes[name] = std::make_shared<Mesh>();
    Mesh* newMesh = m_meshes[name].get();

    newMesh->vertex_count = mesh.vertices.size();
    newMesh->vertices = mesh.vertices;
    newMesh->uvs = mesh.uvs;
    newMesh->normals = mesh.normals;
    if( mesh.vertices.size() % 3 != 0 ||
        mesh.uvs.size() % 3 != 0 ||
        mesh.uvs.size() % 3 != 0 ||
        (mesh.vertices.size() & mesh.uvs.size() & mesh.normals.size()) != mesh.vertices.size())
    {
        Game::logger().log("Failed to create mesh because mesh data is not valid.", Logger::Warning);

        unloadMesh(name);
        return false;
    }  

    for(size_t i = 0; i < newMesh->vertex_count; i += 3)
    {
        Vector3f& v0 = mesh.vertices[i + 0];
        Vector3f& v1 = mesh.vertices[i + 1];
        Vector3f& v2 = mesh.vertices[i + 2];

        Vector2f& uv0 = mesh.uvs[i + 0];
        Vector2f& uv1 = mesh.uvs[i + 1];
        Vector2f& uv2 = mesh.uvs[i + 2];

        Vector3f deltaPos1 = v1 - v0;
        Vector3f deltaPos2 = v2 - v0;

        Vector2f deltaUV1 = uv1 - uv0;
        Vector2f deltaUV2 = uv2 - uv0;

        float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
        Vector3f tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
        Vector3f bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;
    
        newMesh->tangents.push_back(tangent);
        newMesh->tangents.push_back(tangent);
        newMesh->tangents.push_back(tangent);

        newMesh->bitangents.push_back(bitangent);
        newMesh->bitangents.push_back(bitangent);
        newMesh->bitangents.push_back(bitangent);
    }

    //Upload Mesh --> TODO

    return true;
}
bool AssetManager::unloadMesh(std::string name) noexcept
{
    if(!meshExists(name))
    {
        Game::logger().log("Failed to unload mesh '" + name + "' because it does not exists.", Logger::Warning);
        return false;
    }

    //Unload Mesh --> TODO

    m_meshes.erase(name);
    return true;
}
bool AssetManager::meshExists(std::string name) noexcept
{
    return m_meshes.find(name) != m_meshes.end();
}
std::shared_ptr<const Mesh> AssetManager::getMesh(std::string name) noexcept
{
    try
    {
        return std::const_pointer_cast<const Mesh>(m_meshes.at(name));
    }   
    catch(std::out_of_range e)
    {
        Game::interrupt("Failed to access mesh '" + name + "'");
    }
}

bool AssetManager::loadMaterial(std::string name, MaterialData& material) noexcept
{
    if(materialExists(name))
    {
        Game::logger().log("Failed to load material '" + name + "' because it already exists.", Logger::Warning);
        return false;
    }

    m_materials[name] = std::make_shared<Material>();
    Material* newMaterial = m_materials[name].get();

    if(!material.diffuseTexture.empty())
        newMaterial->diffuseTexture = getTexture(material.diffuseTexture);
    else
        newMaterial->diffuseTexture = nullptr;

    newMaterial->diffuseUniform = material.diffuseUniform;

    if(!material.normalTexture.empty())
        newMaterial->normalTexture = getTexture(material.normalTexture);
    else
        newMaterial->normalTexture = nullptr;

    return true;
}
bool AssetManager::unloadMaterial(std::string name) noexcept
{
    if(!materialExists(name))
    {
        Game::logger().log("Failed to unload material '" + name + "' because it does not exists.", Logger::Warning);
        return false;
    }

    m_materials.erase(name);

    return true;
}
bool AssetManager::materialExists(std::string name) noexcept
{
    return m_materials.find(name) != m_materials.end();
}
std::shared_ptr<const Material> AssetManager::getMaterial(std::string name) noexcept
{
    try
    {
        return std::const_pointer_cast<const Material>(m_materials.at(name));
    }
    catch(std::out_of_range e)
    {
        Game::interrupt("Failed to access material '" + name + "'");
    }   
}

bool AssetManager::loadModel(std::string name, Path path) noexcept
{
    if(modelExists(name))
    {
        Game::logger().log("Failed to load model '" + name + "' because it already exists.", Logger::Warning);
        return false;
    }

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string err;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path.c_str());

    if(!ret)
    {
        Game::logger().log("Failed to load model '" + name + "'", Logger::Warning);
        Game::logger().log("TINYOBJ Error: " + err);
        return false;
    }

    for(const auto& shape : shapes)
    {
        for(const auto& index : shape.mesh.indices)
        {
            
        }
    }

    //Loop over shapes
    for(size_t s = 0; s < shapes.size(); s++)
    {
        //Loop over triangles
        size_t index_offset = 0;
        for(size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
        {
            int fv = shapes[s].mesh.num_face_vertices[f];

            //Loop over vertices in the face
            for(size_t v = 0; v < fv; v++)
            {
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                tinyobj::real_t vx = attrib.vertices[3*idx.vertex_index+0];
                tinyobj::real_t vy = attrib.vertices[3*idx.vertex_index+1];
                tinyobj::real_t vz = attrib.vertices[3*idx.vertex_index+2];
                tinyobj::real_t nx = attrib.normals[3*idx.normal_index+0];
                tinyobj::real_t ny = attrib.normals[3*idx.normal_index+1];
                tinyobj::real_t nz = attrib.normals[3*idx.normal_index+2];
                tinyobj::real_t tx = attrib.texcoords[2*idx.texcoord_index+0];
                tinyobj::real_t ty = attrib.texcoords[2*idx.texcoord_index+1];
            }
            index_offset += fv;

            shapes[s].mesh.material_ids[f];
        }
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

