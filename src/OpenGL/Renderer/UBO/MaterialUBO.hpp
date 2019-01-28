#pragma once

//////////////
//HEADERS
//////////////
#include <Core/Utility/Color.hpp>
#include <OpenGL/Export.hpp>

#include <GL/glew.h>

#include <vector>

namespace ax
{
    class MaterialGL;

    class AXION_GL_API MaterialUBO
    {
    private:
        struct MaterialUBOData
        {
            GLuint flags;
            float pad[3];
            Color3 diffuseColor;
            float pad1;
            //float specularUniform;
        };

    public:
        MaterialUBO();
        ~MaterialUBO();

        void load(MaterialGL& material) noexcept;
        void unload(MaterialGL& material) noexcept;
        void updateMaterial(const MaterialGL& material) noexcept;

    private:
        GLuint m_ubo;
        size_t m_next = 0;
        std::vector<GLuint> m_free;
    };
}