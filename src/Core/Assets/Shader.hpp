#pragma once

/////////////
//HEADERS
/////////////
#include <Core/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Utility/Path.hpp>

#include <string>
#include <memory>
#include <unordered_map>

namespace ax
{
    struct AXION_CORE_API Shader
    {
        std::string name;

        std::string vertex;
        std::string fragment;
        
        Id handle;
    };

    class AXION_CORE_API ShaderManager
    {
    public:
        std::shared_ptr<const Shader> operator()(std::string name) const noexcept;
        std::shared_ptr<const Shader> load(std::string name, Path vertex, Path fragment) noexcept;
        bool unload(std::string name) noexcept;
        bool isLoaded(std::string name) const noexcept;

        void dispose() noexcept;
        void log() const noexcept;

    private:
        std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaders;
    };
}