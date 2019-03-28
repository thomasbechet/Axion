#pragma once

#include <OpenGL/Export.hpp>
#include <Core/Math/Vector.hpp>
#include <Core/Utility/Color.hpp>

#include <GL/glew.h>

namespace ax
{
    class AXION_GL_API ConstantsUBO
    {
    private:
        struct ConstantsUBOData
        {
            Vector2u resolution;
        };

    public:
        ConstantsUBO();
        ~ConstantsUBO();

        void setResolution(const Vector2u& resolution) noexcept;
        void update() const noexcept;

    private:
        GLuint m_ubo;
        ConstantsUBOData m_constants;
    };
}