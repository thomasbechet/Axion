#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>

namespace ax
{
    class AXION_CORE_API ShaderManager
    {
    public:
        AssetReference<Shader> operator()(std::string name) const noexcept;
        AssetReference<Shader> create(std::string name, Path vertex, Path fragment) noexcept;
        bool destroy(std::string name) noexcept;
        bool exists(std::string name) const noexcept;

        void dispose() noexcept;
        void log() const noexcept;

    private:
        std::unordered_map<std::string, std::unique_ptr<AssetHolder<Shader>>> m_shaders;
    };
}