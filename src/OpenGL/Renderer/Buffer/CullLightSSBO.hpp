#pragma once

#include <OpenGL/Export.hpp>
#include <Core/Math/Vector.hpp>

#include <GL/glew.h>

namespace ax
{
    class AXION_GL_API CullLightSSBO
    {
    public:
        CullLightSSBO(Vector2u resolution);
        ~CullLightSSBO();

        void setResolution(Vector2u resolution) noexcept;
        Vector2u getResolution() const noexcept;

        static Vector2u dispatchSize(Vector2u resolution) noexcept;

    private:
        void create(Vector2u resolution) noexcept;
        void destroy() noexcept;

    private:
        GLuint m_ssbo;
        Vector2u m_resolution;
    };
}