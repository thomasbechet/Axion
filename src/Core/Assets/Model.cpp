#include <Core/Assets/Model.hpp>

#include <Core/Assets/AssetManager.hpp>
#include <Core/Logger/Logger.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader/tiny_obj_loader.h>

using namespace ax;

Model::Model(){}
Model::Model(std::string name)
{
    m_name = name;
}
Model::~Model()
{
    unload();
}

bool Model::loadFromFile(Path path) noexcept
{
    unload();

    if(path.extension() == ".obj")
        return loadObjModel(path);
    else
        return false;
}
bool Model::unload(bool tryDestroyMeshes, bool tryDestroyMaterials, bool tryDestroyTextures) noexcept
{
    if(m_isLoaded)
    {
        if(tryDestroyMeshes)
        {
            for(auto it = m_meshes.begin(); it != m_meshes.end(); it++)
            {
                std::string meshName = it->get()->getName();
                it->reset();
                Engine::assets().mesh.destroy(meshName);
            }
        }
        m_meshes.clear();
        if(tryDestroyMaterials)
        {
            for(auto& it : m_materials)
            {
                std::string materialName = it.get()->getName();
                it.reset();
                Engine::assets().material.destroy(materialName, tryDestroyTextures);            
            }
        }
        m_materials.clear();
    }

    m_isLoaded = false;

    return true;
}
bool Model::isLoaded() const noexcept
{
    return m_isLoaded;
}

std::string Model::getName() const noexcept
{
    return m_name;
}

const std::vector<AssetReference<Mesh>>& Model::getMeshes() const noexcept
{
    return m_meshes;
}
const std::vector<AssetReference<Material>>& Model::getMaterials() const noexcept
{
    return m_materials;
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
        Engine::logger().log("Failed to load model '" + m_name + "'", Logger::Warning);
        Engine::logger().log("TINYOBJ Error: " + err);
        return false;
    }

    //Loading materials
    for(const auto& material : materials)
    {
        if(!Engine::assets().material.exists(material.name))
        {
            MaterialParameters data;

            //Diffuse Texture
            Path diffusePath = path.directory() + material.diffuse_texname;
            bool hasDiffuseTex = !diffusePath.filename().empty() &&
                (Engine::assets().texture.exists(diffusePath.filename()) ||
                 Engine::assets().texture.create(diffusePath.filename(), diffusePath.path()));
            
            if(hasDiffuseTex)
                data.diffuseTexture = diffusePath.filename();
            else
            {
                data.diffuseColor.r = material.diffuse[0];
                data.diffuseColor.g = material.diffuse[1];
                data.diffuseColor.b = material.diffuse[2];
            }

            //Normal Texture
            Path normalPath = path.directory() + material.normal_texname;
            Path bumpPath = path.directory() + material.bump_texname;

            if(!normalPath.filename().empty())
            {
                if(Engine::assets().texture.exists(normalPath.filename()) ||
                    Engine::assets().texture.create(normalPath.filename(), normalPath.path()))
                {
                    data.normalTexture = normalPath.filename();
                    data.isBumpTexture = false;
                }
            }
            else if(!bumpPath.filename().empty())
            {
                if(Engine::assets().texture.exists(bumpPath.filename()) ||
                    Engine::assets().texture.create(bumpPath.filename(), bumpPath.path()))
                {
                    data.normalTexture = bumpPath.filename();
                    data.isBumpTexture = true;
                }
            }

            //Load material as assets
            Engine::assets().material.create(material.name, data);
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

                vertex.color.x = attrib.colors[3 * idx.vertex_index + 0];
                vertex.color.y = attrib.colors[3 * idx.vertex_index + 1];
                vertex.color.z = attrib.colors[3 * idx.vertex_index + 2];

                meshes[materialId].push_back(vertex);
            }

            index_offset += fv;
        }
    }

    //Loading models
    for(auto it = meshes.begin(); it != meshes.end(); it++)
    {
        size_t i = std::distance(meshes.begin(), it);
        
        std::string meshName = m_name + "_" + std::to_string(i);
        Engine::assets().mesh.create(meshName, it->second, true, attrib.normals.empty());
        m_meshes.emplace_back(Engine::assets().mesh(meshName));

        if(it->first != -1)
        {
            std::string materialName = materials[it->first].name;
            m_materials.emplace_back(Engine::assets().material(materialName));
        }
        else
        {
            m_materials.emplace_back(Engine::assets().material(Material::Default));
        }
    }

    m_isLoaded = true;

    return true;
}