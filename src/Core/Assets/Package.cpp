#include <Core/Assets/AssetManager.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Logger/Logger.hpp>

#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>

using namespace ax;

std::shared_ptr<const Package> PackageManager::operator()(std::string name) const noexcept
{
    try
    {
        return std::const_pointer_cast<const Package>(m_packages.at(name));
    }
    catch(std::out_of_range e)
    {
        Engine::interrupt("Failed to access package '" + name + "'");
    }
}
std::shared_ptr<const Package> PackageManager::load(Path path) noexcept
{
    rapidxml::file<> file(path.c_str());
    rapidxml::xml_document<> doc;
    try
    {
        doc.parse<0>(file.data());
    }
    catch(rapidxml::parse_error& e)
    {   
        Engine::logger().log("Failed to parse package file " + path.path(), Logger::Warning);
        return nullptr;
    }
    
    rapidxml::xml_node<>* package_node = doc.first_node("package");
    if(!package_node)
    {
        Engine::logger().log("Failed to load package " + path.path() + " because it does not contain 'package' node", Logger::Warning);
        return nullptr;
    }
    
    std::string name = path.filename();
    if(package_node->first_attribute("name"))
        name = package_node->first_attribute("name")->value();
    
    Path directory = "";
    if(package_node->first_attribute("directory")) 
        directory = Path(package_node->first_attribute("directory")->value());
    

    if(isLoaded(name))
    {
        Engine::logger().log("Failed to load package '" + name + "' because it already exists.", Logger::Warning);
        return nullptr;
    }

    m_packages.emplace(name, std::make_shared<Package>());
    Package* package = m_packages.at(name).get();
    package->name = name;

    for(rapidxml::xml_node<>* texture_node = package_node->first_node("texture"); texture_node; texture_node = texture_node->next_sibling("texture"))
    {
        if(texture_node->first_attribute("src"))
        {
            Path texture_path = directory + texture_node->first_attribute("src")->value();

            std::string texture_name = texture_path.filename();
            if(texture_node->first_attribute("name"))
                texture_name = texture_node->first_attribute("name")->value();

            if(Engine::assets().texture.load(texture_name, texture_path))
                package->textures.emplace_back(Engine::assets().texture(texture_name));
        }
    }

    /*for(rapidxml::xml_node<>* mesh_node = package_node->first_node("mesh"); mesh_node; mesh_node = mesh_node->next_sibling("mesh"))
    {
        Path mesh_path = directory + mesh_node->value();
        std::string mesh_name = mesh_path.filename();
        if(mesh_node->first_attribute("name"))
            mesh_name = mesh_node->first_attribute("name")->value();

        if(loadMesh(mesh_name, mesh_path))
            package->meshes.emplace(mesh_name, getMesh(mesh_name));
    }*/

    /*for(rapidxml::xml_node<>* material_node = package_node->first_node("material"); material_node; material_node = material_node->next_sibling("material"))
    {
        Path material_path = directory + material_node->value();
        std::string material_name = material_path.filename();
        if(material_node->first_attribute("name"))
            material_name = material_node->first_attribute("name")->value();

        if(loadMaterial(material_name, material_path))
            package->materials.emplace(material_name, getMaterial(material_name));
    }*/

    for(rapidxml::xml_node<>* model_node = package_node->first_node("model"); model_node; model_node = model_node->next_sibling("model"))
    {
        if(model_node->first_attribute("src"))
        {
            Path model_path = directory + model_node->first_attribute("src")->value();

            std::string model_name = model_path.filename();
            if(model_node->first_attribute("name"))
                model_name = model_node->first_attribute("name")->value();

            if(Engine::assets().model.load(model_name, model_path))
                package->models.emplace_back(Engine::assets().model(model_name));
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
                if(Engine::assets().shader.load(shader_name, vertex_path, fragment_path))
                    package->shaders.emplace_back(Engine::assets().shader(shader_name));
            }
        }
    }

    return m_packages.at(name);
}
bool PackageManager::unload(std::string name) noexcept
{
    if(!isLoaded(name))
    {
        Engine::logger().log("Failed to unload package '" + name + "' because it does not exists.", Logger::Warning);
        return false;
    }

    Package* package = m_packages.at(name).get();

    for(auto it = package->models.begin(); it != package->models.end(); it++)
    {
        std::string modelName = it->get()->name;
        it->reset();
        Engine::assets().model.unload(modelName);
    }
    package->models.clear();
    for(auto it = package->textures.begin(); it != package->textures.end(); it++)
    {
        std::string textureName = it->get()->name;
        it->reset();
        Engine::assets().texture.unload(textureName);
    }
    package->textures.clear();
    for(auto it = package->meshes.begin(); it != package->meshes.end(); it++)
    {
        std::string meshName = it->get()->name;
        it->reset();
        Engine::assets().mesh.unload(meshName);
    }
    package->meshes.clear();
    for(auto it = package->materials.begin(); it != package->materials.end(); it++)
    {
        std::string materialName = it->get()->name;
        it->reset();
        Engine::assets().material.unload(materialName);
    }  
    package->materials.clear();

    if(m_packages.at(name).use_count() != 1) return false;

    m_packages.erase(name);

    return true;
}
bool PackageManager::isLoaded(std::string name) const noexcept
{
    return m_packages.find(name) != m_packages.end();
}

void PackageManager::dispose() noexcept
{
    std::vector<std::string> keys;
    keys.reserve(m_packages.size());
    for(auto it : m_packages)
        keys.emplace_back(it.second->name);

    for(auto it : keys) unload(it);
}
void PackageManager::log() const noexcept
{
    Engine::logger().log("[   PACKAGE   ]", Logger::Info);
    
    for(auto it = m_packages.begin(); it != m_packages.end(); it++)
    {
        Engine::logger().log("- " + it->second.get()->name, Logger::Info);
    }
}