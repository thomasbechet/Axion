#pragma once

#include <Core/Export.hpp>
#include <Core/Asset/Shader.hpp>
#include <Core/Asset/AssetReference.hpp>

namespace ax
{
    class AXION_CORE_API ShaderManager
    {
    public:
        AssetReference<Shader> operator()(std::string name) const noexcept;
        AssetReference<Shader> loadFromFile(std::string name, Path file) noexcept;
        AssetReference<Shader> loadFromJson(std::string name, const std::string& json) noexcept;
        bool unload(std::string name) noexcept;
        bool exists(std::string name) const noexcept;

        void dispose() noexcept;
        void log() const noexcept;

    private:
        std::unordered_map<std::string, std::unique_ptr<AssetHolder<Shader>>> m_shaders;
    };
}