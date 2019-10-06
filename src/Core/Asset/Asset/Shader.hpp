#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/Path.hpp>
#include <Core/Renderer/Asset/RendererShader.hpp>
#include <Core/Asset/Asset.hpp>

#include <string>

namespace ax
{
    class AXION_CORE_API Shader : public Asset
    {
    public:
        struct Parameters
        {
            Path source;
            std::string json;
        };

    public:
        static const std::string name;

        Shader(std::string name, const Parameters& parameters);

        std::string getVertexCode() const noexcept;
        std::string getFragmentCode() const noexcept;

        RendererShaderHandle getHandle() const noexcept;

    private:
        bool onLoad() noexcept override;
        bool onValidate() noexcept override;
        bool onUnload() noexcept override;
        void onError() noexcept override;

    private:
        Parameters m_parameters;

        std::string m_vertex;
        std::string m_fragment;

        RendererShaderHandle m_handle;

        std::string m_error;
    };
}