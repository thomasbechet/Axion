#pragma once

//////////////
//HEADERS
//////////////
#include <OpenGL/Export.hpp>
#include <Core/Math/Vector.hpp>
#include <Core/Utility/Color.hpp>

#include <GL/glew.h>

namespace ax
{
    class AXION_GL_API ShaderConstantsUBO
    {
    private:
        struct ShaderConstantsUBOData
        {
            Vector2u resolution;
        };

    public:
        ShaderConstantsUBO();
        ~ShaderConstantsUBO();

        void setResolution(const Vector2u& resolution) noexcept;
        void update() const noexcept;

    private:
        GLuint m_ubo;
        ShaderConstantsUBOData m_constants;
    };
}