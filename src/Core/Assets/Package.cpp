#include <Core/Assets/AssetManager.hpp>

#include <Core/Context/Game.hpp>
#include <Core/Logger/Logger.hpp>

#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>

using namespace ax;

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

    m_packages.emplace(name, std::make_shared<Package>());
    Package* package = m_packages.at(name).get();
    package->name = name;

    for(rapidxml::xml_node<>* texture_node = package_node->first_node("texture"); texture_node; texture_node = texture_node->next_sibling("texture"))
    {
        Path texture_path = directory + texture_node->value();
        std::string texture_name = texture_path.filename();
        if(texture_node->first_attribute("name"))
            texture_name = texture_node->first_attribute("name")->value();

        if(loadTexture(texture_name, texture_path))
            package->textures.emplace_back(getTexture(texture_name));
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
        Path model_path = directory + model_node->value();
        std::string model_name = model_path.filename();
        if(model_node->first_attribute("name"))
            model_name = model_node->first_attribute("name")->value();

        if(loadModel(model_name, model_path))
            package->models.emplace_back(getModel(model_name));
    }

    return true;
}
bool AssetManager::unloadPackage(std::string name) noexcept
{
    if(!packageExists(name))
    {
        Game::logger().log("Failed to unload package '" + name + "' because it does not exists.", Logger::Warning);
        return false;
    }

    Package* package = m_packages.at(name).get();

    for(auto it = package->models.begin(); it != package->models.end(); it++)
    {
        std::string modelName = it->get()->name;
        it->reset();
        unloadModel(modelName);
    }
    package->models.clear();
    for(auto it = package->textures.begin(); it != package->textures.end(); it++)
    {
        std::string textureName = it->get()->name;
        it->reset();
        unloadTexture(textureName);
    }
    package->textures.clear();
    for(auto it = package->meshes.begin(); it != package->meshes.end(); it++)
    {
        std::string meshName = it->get()->name;
        it->reset();
        unloadMesh(meshName);
    }
    package->meshes.clear();
    for(auto it = package->materials.begin(); it != package->materials.end(); it++)
    {
        std::string materialName = it->get()->name;
        it->reset();
        unloadMaterial(materialName);
    }  
    package->materials.clear();

    if(m_packages.at(name).use_count() == 1) return false;

    m_packages.erase(name);

    return true;
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