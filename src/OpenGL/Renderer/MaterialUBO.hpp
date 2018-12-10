#pragma once

//////////////
//HEADERS
//////////////
#include <Core/Utility/Color.hpp>
#include <OpenGL/Export.hpp>

#include <GL/glew.h>

#include <vector>

#define MATERIAL_MAX_NUMBER 50
#define MATERIAL_BINDING_POINT 1
#define MATERIAL_USE_DIFFUSE_TEXTURE 1
#define MATERIAL_USE_NORMAL_TEXTURE 2
#define MATERIAL_IS_BUMP_TEXTURE 4
#define MATERIAL_USE_SPECULAR_TEXTURE 8

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
            Color diffuseColor;
        };

    public:
        MaterialUBO();
        ~MaterialUBO();

        void load(MaterialGL& material) noexcept;
        void unload(MaterialGL& material) noexcept;
        void update(const MaterialGL& material) noexcept;

    private:
        GLuint m_ubo;
        size_t m_next = 0;
        std::vector<GLuint> m_free;
    };
}