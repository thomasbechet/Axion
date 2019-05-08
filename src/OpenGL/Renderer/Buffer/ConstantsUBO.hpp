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
            Vector2u viewportResolution;
            Vector2u windowSize;
        };

    public:
        ConstantsUBO();
        ~ConstantsUBO();

        void setViewportResolution(const Vector2u& resolution) noexcept;
        void setWindowSize(const Vector2u& size) noexcept;
        void update() noexcept;

    private:
        GLuint m_ubo;
        ConstantsUBOData m_constants;
    };
}