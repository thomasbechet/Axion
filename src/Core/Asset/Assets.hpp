#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/Path.hpp>
#include <Core/Math/Geometry/Vertex.hpp>
#include <Core/Asset/AssetLoader.hpp>
#include <Core/Asset/AssetManager.hpp>
#include <Core/Asset/Asset/Texture.hpp>
#include <Core/Asset/Asset/Mesh.hpp>
#include <Core/Asset/Asset/Material.hpp>
#include <Core/Asset/Asset/Model.hpp>
#include <Core/Asset/Asset/Package.hpp>
#include <Core/Asset/Asset/Shader.hpp>

namespace ax
{
    class AXION_CORE_API Assets
    {
    public:
        Assets();
        ~Assets();

        void dispose() noexcept;
        void log() const noexcept;
        unsigned getTotalPending() noexcept;
        std::string getCurrentAssetName() noexcept;

        AssetManager<Texture> texture;
        AssetManager<Mesh> mesh;
        AssetManager<Shader> shader;
        AssetManager<Material> material;
        AssetManager<Model> model;
        AssetManager<Package> package;

    private:
        AssetLoader m_assetLoader;
    };
}