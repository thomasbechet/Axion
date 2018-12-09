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
    class AXION_CORE_API Shader
    {
    public:
        Shader();
        Shader(std::string name);

        bool loadFromFile(Path vertex, Path fragment) noexcept;
        bool unload() noexcept;
        bool isLoaded() const noexcept;

        std::string getName() const noexcept;
        std::string getVertexCode() const noexcept;
        std::string getFragmentCode() const noexcept;

        Id getHandle() const noexcept;

    private:
        std::string m_name;
        
        bool m_isLoaded = false;

        std::string m_vertex;
        std::string m_fragment;

        Id m_handle;
    };
}