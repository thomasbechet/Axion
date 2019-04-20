#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Utility/Color.hpp>
#include <Core/Renderer/Asset/RendererTexture.hpp>
#include <Core/Renderer/Asset/RendererShader.hpp>

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
}