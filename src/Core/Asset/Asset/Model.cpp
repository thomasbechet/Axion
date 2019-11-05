#include <Core/Asset/Asset/Model.hpp>

#include <Core/Asset/AssetModule.ipp>
#include <Core/Asset/JsonAttributes.hpp>
#include <Core/Utility/Json.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader/tiny_obj_loader.h>

using namespace ax;

Model::Model(const std::string& name, const Parameters& parameters) :
    Asset(name, identifier),
    m_parameters(parameters)
{

}

const std::vector<AssetReference<Mesh>>& Model::getMeshes() const noexcept
{
    return m_meshes;
}
const std::vector<AssetReference<Material>>& Model::getMaterials() const noexcept
{
    return m_materials;
}

bool Model::onLoad() noexcept
{
    if(!m_parameters.source.empty())
    {
        if(m_parameters.source.extension() == ".obj")
        {
            return loadObjModel(m_parameters.source);
        }
        else
        {
            logLoadError("Unknown extension file '" + m_parameters.source.extension() + "'");
            return false;
        }
    }
    else if(!m_parameters.json.is_null())
    {
        try
        {
            if(m_parameters.json[JsonAttributes::type] != Model::identifier)
            {
                logLoadError("Loading <" + Model::identifier + "> without '" + Model::identifier + "' value for '" + JsonAttributes::type + "' attribute");
                return false;
            }
        }
        catch(const std::exception& e)
        {
            logLoadError("Loading <" + Model::identifier + "> without '" + JsonAttributes::type + "' attribute");
            return false;
        }

        try
        {
            Path source = m_parameters.json[JsonAttributes::source].get<std::string>();
            if(source.extension() == ".obj")
            {
                return loadObjModel(source);
            }
            else
            {
                logLoadError("Unknown extension file '" + source.extension() + "'");
                return false;
            }
        }
        catch(const std::exception& e)
        {
            logLoadError("Loading <" + Model::identifier + "> without '" + JsonAttributes::source + "' attribute");
            return false;
        }
    }

    logLoadError("Loading <" + Model::identifier + "> without inputs parameters");
    return false;
}
bool Model::onValidate() noexcept
{
    for(auto& it : m_dummyModels)
    {
        m_meshes.emplace_back(Engine::asset().get<Mesh>(it.first));
        m_materials.emplace_back(Engine::asset().get<Material>(it.second));
    }

    return true;
}
bool Model::onUnload() noexcept
{
    if(m_parameters.tryDestroyMeshes)
    {
        for(auto it = m_meshes.begin(); it != m_meshes.end(); it++)
        {
            std::string meshName = it->get()->getName();
            it->reset();
            Engine::asset().unload<Mesh>(meshName);
        }
    }
    m_meshes.clear();
    if(m_parameters.tryDestroyMaterials)
    {
        for(auto& it : m_materials)
        {
            std::string materialName = it.get()->getName();
            it.reset();
            Engine::asset().unload<Material>(materialName);            
        }
    }
    m_materials.clear();

    return true;
}

bool Model::loadObjModel(Path path) noexcept
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string err;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path.c_str(), path.directory().c_str(), true);
    if(!ret)
    {
        logLoadError("TINYOBJ Error: " + err);
        return false;
    }

    //Loading materials
    for(const auto& material : materials)
    {
        if(!Engine::asset().exists<Material>(material.name))
        {
            Material::Parameters materialParameters;

            //Diffuse Texture
            Path diffusePath = path.directory() + material.diffuse_texname;
            if(!diffusePath.filename().empty())
            {
                if(!Engine::asset().exists<Texture>(diffusePath.filename()))
                {
                    Texture::Parameters textureParameters;
                    textureParameters.source = diffusePath;
                    if(m_parameters.asyncLoading)
                        Engine::asset().loadAsync<Texture>(diffusePath.filename(), textureParameters);
                    else
                        Engine::asset().load<Texture>(diffusePath.filename(), textureParameters);
                }
                materialParameters.diffuseTexture = diffusePath.filename();
            }
            else
            {
                materialParameters.diffuseColor.r = material.diffuse[0];
                materialParameters.diffuseColor.g = material.diffuse[1];
                materialParameters.diffuseColor.b = material.diffuse[2];
            }

            //Normal Texture
            Path normalPath = path.directory() + material.normal_texname;
            Path bumpPath = path.directory() + material.bump_texname;
            if(!normalPath.filename().empty())
            {
                if(!Engine::asset().exists<Texture>(normalPath.filename()))
                {
                    Texture::Parameters textureParameters;
                    textureParameters.source = normalPath;
                    if(m_parameters.asyncLoading)
                        Engine::asset().loadAsync<Texture>(normalPath.filename(), textureParameters);
                    else
                        Engine::asset().load<Texture>(normalPath.filename(), textureParameters);
                }
                materialParameters.normalTexture = normalPath.filename();
                materialParameters.isBumpTexture = false;
            }
            else if(!bumpPath.filename().empty())
            {
                if(!Engine::asset().exists<Texture>(bumpPath.filename()))
                {
                    Texture::Parameters textureParameters;
                    textureParameters.source = bumpPath;
                    if(m_parameters.asyncLoading)
                        Engine::asset().loadAsync<Texture>(bumpPath.filename(), textureParameters);
                    else
                        Engine::asset().load<Texture>(bumpPath.filename(), textureParameters);
                }
                materialParameters.normalTexture = bumpPath.filename();
                materialParameters.isBumpTexture = true;
            }

            //Specular
            Path specularPath = path.directory() + material.specular_texname;
            if(!specularPath.filename().empty())
            {
                if(!Engine::asset().exists<Texture>(specularPath.filename()))
                {
                    Texture::Parameters textureParameters;
                    textureParameters.source = specularPath;
                    if(m_parameters.asyncLoading)
                        Engine::asset().loadAsync<Texture>(specularPath.filename(), textureParameters);
                    else
                        Engine::asset().load<Texture>(specularPath.filename(), textureParameters);
                }
                materialParameters.specularTexture = specularPath.filename();
            }
            else
            {
                materialParameters.specularUniform = material.shininess;
            }

            //Load material as assets
            if(m_parameters.asyncLoading)
                Engine::asset().loadAsync<Material>(material.name, materialParameters);
            else
                Engine::asset().load<Material>(material.name, materialParameters);
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

                meshes[materialId].push_back(vertex);
            }

            index_offset += fv;
        }
    }

    //Loading models
    for(auto it = meshes.begin(); it != meshes.end(); it++)
    {
        size_t i = std::distance(meshes.begin(), it);
        
        std::string meshName = getName() + "_" + std::to_string(i);
        Mesh::Parameters meshParameters;
        meshParameters.vertices = it->second;
        meshParameters.computeTangent = true;
        meshParameters.computeNormal = attrib.normals.empty();
        if(m_parameters.asyncLoading)
            Engine::asset().loadAsync<Mesh>(meshName, meshParameters);
        else
            Engine::asset().load<Mesh>(meshName, meshParameters);

        if(it->first != -1)
        {
            std::string materialName = materials[it->first].name;
            m_dummyModels.emplace_back(std::make_pair(meshName, materialName));
        }
        else
        {
            m_dummyModels.emplace_back(std::make_pair(meshName, Material::Default));
        }
    }

    return true;
}