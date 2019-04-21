#pragma once

#include <Core/Export.hpp>
#include <Core/Renderer/Asset/RendererTexture.hpp>
#include <Core/Renderer/Asset/RendererShader.hpp>
#include <Core/Utility/Color.hpp>

namespace ax
{
    struct AXION_CORE_API RendererMaterialParameters
    {
        RendererTextureHandle diffuseTexture = nullptr;
        Color3 diffuseColor = Color3(1.0f, 1.0f, 1.0f);
        bool useDiffuseTexture = false;
        bool useDiffuseColor = false;

        RendererTextureHandle normalTexture = nullptr;
        bool useNormalTexture = false;
        bool isBumpTexture = false;

        RendererTextureHandle specularTexture = nullptr;
        float specularUniform = 1.0f;
        bool useSpecularTexture = false;

        RendererShaderHandle shader = nullptr;
    };

    class AXION_CORE_API RendererMaterial
    {
    public:
        virtual void update(const RendererMaterialParameters& settings) = 0;
    };

    class AXION_CORE_API NullRendererMaterial : public RendererMaterial
    {
    public:
        void update(const RendererMaterialParameters& settings) override {}
    };

    using RendererMaterialHandle = RendererMaterial*;
}