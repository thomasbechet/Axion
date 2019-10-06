#include <Core/Asset/Asset/Package.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Logger/Logger.hpp>
#include <Core/Asset/Assets.hpp>
#include <Core/Asset/JsonAttributes.hpp>

#include <json/json.hpp>

#include <fstream>

using namespace ax;

const std::string Package::name = "Package";

Package::Package(std::string name, const Parameters& parameters) :
    Asset(name),
    m_parameters(parameters)
{

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

bool Package::onLoad() noexcept
{
    if(!m_parameters.source.empty())
    {
        if(m_parameters.source.extension() != ".json")
        {
            m_error = "Failed to load package from file '" + m_parameters.source + "'";
            return false;
        }

        std::ifstream jsonFile(m_parameters.source.path());
        if(!jsonFile.is_open())
        {
            m_error = "Failed to load package from file '" + m_parameters.source.path() + "'";
            return false;
        }
        std::string jsonBuffer{std::istreambuf_iterator<char>(jsonFile), std::istreambuf_iterator<char>()};

        return loadFromJsonAsync(jsonBuffer);
    }
    else if(!m_parameters.json.empty())
    {
        return loadFromJsonAsync(m_parameters.json);
    }
    else
    {
        return false;
    }
}
bool Package::onValidate() noexcept
{
    for(auto& it : m_dummyMaterials) m_materials.emplace_back(Engine::assets().material(it));
    m_dummyMaterials.clear();
    for(auto& it : m_dummyMeshes) m_meshes.emplace_back(Engine::assets().mesh(it));
    m_dummyMeshes.clear();
    for(auto& it : m_dummyModels) m_models.emplace_back(Engine::assets().model(it));
    m_dummyMaterials.clear();
    for(auto& it : m_dummyShaders) m_shaders.emplace_back(Engine::assets().shader(it));
    m_dummyShaders.clear();
    for(auto& it : m_dummyTextures) m_textures.emplace_back(Engine::assets().texture(it));
    m_dummyTextures.clear();

    return true;
}
bool Package::onUnload() noexcept
{
    for(auto it = m_materials.begin(); it != m_materials.end(); it++)
    {
        std::string materialName = it->get()->getName();
        it->reset();
        Engine::assets().material.unload(materialName);
    }
    m_materials.clear();
    for(auto it = m_models.begin(); it != m_models.end(); it++)
    {
        std::string modelName = it->get()->getName();
        it->reset();
        Engine::assets().model.unload(modelName);
    }
    m_models.clear();
    for(auto it = m_textures.begin(); it != m_textures.end(); it++)
    {
        std::string textureName = it->get()->getName();
        it->reset();
        Engine::assets().texture.unload(textureName);
    }
    m_textures.clear();
    for(auto it = m_meshes.begin(); it != m_meshes.end(); it++)
    {
        std::string meshName = it->get()->getName();
        it->reset();
        Engine::assets().mesh.unload(meshName);
    }
    m_meshes.clear();
    for(auto it = m_shaders.begin(); it != m_shaders.end(); it++)
    {
        std::string shaderName = it->get()->getName();
        it->reset();
        Engine::assets().shader.unload(shaderName);
    }
    m_shaders.clear();

    return true;
}
void Package::onError() noexcept
{
    Engine::logger().log(m_error, Logger::Warning);
}

bool Package::loadFromJsonAsync(std::string& json) noexcept
{
    //Parse json string
    nlohmann::json j = nlohmann::json::parse(json);

    //Test package type
    auto jType = j.find(JsonAttributes::type);
    if(jType != j.end() && jType->is_string())
    {
        std::string type = jType->get<std::string>(); 
        j.erase(JsonAttributes::type);
        if(type != JsonAttributes::packageType)
        {
            m_error = "Loading package without package type attribute.";
            return false;
        }
    }

    //Load each items
    for(auto& it : j.items())
    {
        nlohmann::json item = it.value();
        std::string name = it.key();
        auto jItemType = item.find(JsonAttributes::type);  
        if(jItemType != item.end() && jItemType->is_string())
        {
            auto jItemName = item.find(JsonAttributes::name);
            if(jItemName != item.end() && jItemName->is_string())
            {
                name = jItemName->get<std::string>();
            }

            std::string itemType = jItemType->get<std::string>();
            if(itemType == JsonAttributes::materialType)
            {
                Material::Parameters materialParameters;
                materialParameters.json = item.dump();
                if(m_parameters.asyncLoading)
                    Engine::assets().material.loadAsync(name, materialParameters);
                else
                    Engine::assets().material.load(name, materialParameters);
                m_dummyMaterials.emplace_back(name);
            }
            else if(itemType == JsonAttributes::meshType)
            {
                Mesh::Parameters meshParameters;
                meshParameters.json = item.dump();
                if(m_parameters.asyncLoading)
                    Engine::assets().mesh.loadAsync(name, meshParameters);
                else
                    Engine::assets().mesh.load(name, meshParameters);
                m_dummyMeshes.emplace_back(name);
            }
            else if(itemType == JsonAttributes::modelType)
            {
                Model::Parameters modelParameters;
                modelParameters.json = item.dump();
                if(m_parameters.asyncLoading)
                    Engine::assets().model.loadAsync(name, modelParameters);
                else
                    Engine::assets().model.load(name, modelParameters);
                m_dummyModels.emplace_back(name);
            }
            else if(itemType == JsonAttributes::packageType)
            {
                
            }
            else if(itemType == JsonAttributes::shaderType)
            {
                Shader::Parameters shaderParameters;
                shaderParameters.json = item.dump();
                if(m_parameters.asyncLoading)
                    Engine::assets().shader.loadAsync(name, shaderParameters);
                else
                    Engine::assets().shader.load(name, shaderParameters);
                m_dummyShaders.emplace_back(name);
            }
            else if(itemType == JsonAttributes::textureType)
            {
                Texture::Parameters textureParameters;
                textureParameters.json = item.dump();
                if(m_parameters.asyncLoading)
                    Engine::assets().texture.loadAsync(name, textureParameters);
                else
                    Engine::assets().texture.load(name, textureParameters);
                m_dummyTextures.emplace_back(name);
            }
        }
    }

    return true;
}