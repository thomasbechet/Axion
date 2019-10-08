#pragma once

#include <Core/Export.hpp>
#include <Core/Asset/Asset.hpp>
#include <Core/Math/Vector.hpp>
#include <Core/Utility/Path.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Renderer/Asset/RendererTexture.hpp>

namespace ax
{
    class AXION_CORE_API Texture : public Asset
    {
    public:
        struct Parameters
        {
            Path source;
            std::string json;
        };

        enum Format
        {
            RGB,
            RGBA,
            R,
            G,
            B
        };

    public:
        static const std::string type;

        Texture(std::string name, const Parameters& parameters);

        std::string getType() const noexcept override;

        Vector2u getSize() const noexcept;
        Format getFormat() const noexcept;
        RendererTextureHandle getHandle() const noexcept;

    private:
        bool onLoad() noexcept override;
        bool onValidate() noexcept override;
        bool onUnload() noexcept override;
        void onError() noexcept override;

    private:
        bool extractSourceFromJson() noexcept;

    private:
        Parameters m_parameters;

        Format m_format = Format::RGB;
        Vector2u m_size = Vector2u(0, 0);
        Byte* m_data = nullptr;
        RendererTextureHandle m_handle;

        std::string m_error;
    };
}