#include <Core/Asset/Package.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Logger/Logger.hpp>
#include <Core/Asset/AssetManager.hpp>

#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>

using namespace ax;

Package::Package(){}
Package::Package(std::string name)
{
    m_name = name;    
}
Package::~Package()
{
    unload();
}

bool Package::loadFromFile(Path path) noexcept
{
    unload();

    rapidxml::file<> file(path.c_str());
    rapidxml::xml_document<> doc;
    try
    {
        doc.parse<0>(file.data());
    }
    catch(rapidxml::parse_error& e)
    {   
        Engine::logger().log("Failed to parse package file " + path.path(), Logger::Warning);
        return false;
    }
    
    rapidxml::xml_node<>* package_node = doc.first_node("package");
    if(!package_node)
    {
        Engine::logger().log("Failed to load package " + path.path() + " because it does not contain 'package' node", Logger::Warning);
        return false;
    }
    
    std::string name = path.filename();
    if(package_node->first_attribute("name"))
        name = package_node->first_attribute("name")->value();
    
    Path directory = "";
    if(package_node->first_attribute("directory")) 
        directory = Path(package_node->first_attribute("directory")->value());

    for(rapidxml::xml_node<>* texture_node = package_node->first_node("texture"); texture_node; texture_node = texture_node->next_sibling("texture"))
    {
        if(texture_node->first_attribute("src"))
        {
            Path texture_path = directory + texture_node->first_attribute("src")->value();

            std::string texture_name = texture_path.filename();
            if(texture_node->first_attribute("name"))
                texture_name = texture_node->first_attribute("name")->value();

            if(Engine::assets().texture.create(texture_name, texture_path))
                m_textures.emplace_back(Engine::assets().texture(texture_name));
        }
    }

    /*for(rapidxml::xml_node<>* mesh_node = package_node->first_node("mesh"); mesh_node; mesh_node = mesh_node->next_sibling("mesh"))
    {
        Path mesh_path = directory + mesh_node->value();
        std::string mesh_name = mesh_path.filename();
        if(mesh_node->first_attribute("name"))
            mesh_name = mesh_node->first_attribute("name")->value();

        if(loadMesh(mesh_name, mesh_path))
            m_meshes.emplace(mesh_name, getMesh(mesh_name));
    }*/

    /*for(rapidxml::xml_node<>* material_node = package_node->first_node("material"); material_node; material_node = material_node->next_sibling("material"))
    {
        Path material_path = directory + material_node->value();
        std::string material_name = material_path.filename();
        if(material_node->first_attribute("name"))
            material_name = material_node->first_attribute("name")->value();

        if(loadMaterial(material_name, material_path))
            m_materials.emplace(material_name, getMaterial(material_name));
    }*/

    for(rapidxml::xml_node<>* model_node = package_node->first_node("model"); model_node; model_node = model_node->next_sibling("model"))
    {
        if(model_node->first_attribute("src"))
        {
            Path model_path = directory + model_node->first_attribute("src")->value();

            std::string model_name = model_path.filename();
            if(model_node->first_attribute("name"))
                model_name = model_node->first_attribute("name")->value();

            if(Engine::assets().model.create(model_name, model_path))
                m_models.emplace_back(Engine::assets().model(model_name));
        }
    }

    for(rapidxml::xml_node<>* shader_node = package_node->first_node("shader"); shader_node; shader_node = shader_node->next_sibling("shader"))
    {
        if(shader_node->first_attribute("vertex") && shader_node->first_attribute("fragment"))
        {
            Path vertex_path = directory + shader_node->first_attribute("vertex")->value();
            Path fragment_path = directory + shader_node->first_attribute("fragment")->value();

            if(shader_node->first_attribute("name"))
            {
                std::string shader_name = shader_node->first_attribute("name")->value();
                if(Engine::assets().shader.create(shader_name, vertex_path, fragment_path))
                    m_shaders.emplace_back(Engine::assets().shader(shader_name));
            }
        }
    }

    m_isLoaded = true;

    return true;
}
bool Package::unload() noexcept
{
    if(m_isLoaded)
    {
        for(auto it = m_materials.begin(); it != m_materials.end(); it++)
        {
            std::string materialName = it->get()->getName();
            it->reset();
            Engine::assets().material.destroy(materialName);
        }
        m_materials.clear();
        for(auto it = m_models.begin(); it != m_models.end(); it++)
        {
            std::string modelName = it->get()->getName();
            it->reset();
            Engine::assets().model.destroy(modelName);
        }
        m_models.clear();
        for(auto it = m_textures.begin(); it != m_textures.end(); it++)
        {
            std::string textureName = it->get()->getName();
            it->reset();
            Engine::assets().texture.destroy(textureName);
        }
        m_textures.clear();
        for(auto it = m_meshes.begin(); it != m_meshes.end(); it++)
        {
            std::string meshName = it->get()->getName();
            it->reset();
            Engine::assets().mesh.destroy(meshName);
        }
        m_meshes.clear();
        for(auto it = m_shaders.begin(); it != m_shaders.end(); it++)
        {
            std::string shaderName = it->get()->getName();
            it->reset();
            Engine::assets().shader.destroy(shaderName);
        }
        m_shaders.clear();
    }

    m_isLoaded = false;
}

std::string Package::getName() const noexcept
{
    return m_name;
}

const std::vector<AssetReference<Texture>>& Package::getTextures() const noexcept
{
    return m_textures;
}
const std::vector<AssetReference<Mesh>>& Package::getMeshes() const noexcept
{
    return m_meshes;
}
const std::vector<AssetReference<Material>>& Package::getMaterials() const noexcept
{
    return m_materials;
}
const std::vector<AssetReference<Model>>& Package::getModels() const noexcept
{
    return m_models;
}
const std::vector<AssetReference<Shader>>& Package::getShaders() const noexcept
{
    return m_shaders;
}