#pragma once

#include <Core/Utility/Color.hpp>
#include <OpenGL/Export.hpp>

#include <GL/glew.h>

#include <vector>

namespace ax
{
    class RendererMaterialGL;

    class AXION_GL_API MaterialUBO
    {
    private:
        struct MaterialUBOData
        {
            GLuint flags;
            float pad0[3];
            Color3 diffuseColor;
            float specularUniform;
        };

    public:
        MaterialUBO();
        ~MaterialUBO();

        void load(RendererMaterialGL& material) noexcept;
        void unload(RendererMaterialGL& material) noexcept;
        void updateMaterial(const RendererMaterialGL& material) noexcept;

    private:
        GLuint m_ubo;
        size_t m_next = 0;
        std::vector<GLuint> m_free;
    };
}