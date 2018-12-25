#pragma once

//////////////
//HEADERS
//////////////
#include <OpenGL/Export.hpp>
#include <Core/Utility/Color.hpp>

#include <GL/glew.h>

#include <vector>

#define POINTLIGHT_MAX_NUMBER 50
#define POINTLIGHT_BINDING_POINT 2

namespace ax
{
    class PointLightGL;

    class AXION_GL_API PointLightUBO
    {
    private:
        struct PointLightUBOData
        {
            Color color;
            float radius;
            float intensity;
        };

    public:
        PointLightUBO();
        ~PointLightUBO();

        void load(PointLightGL& light) noexcept;
        void unload(PointLightGL& light) noexcept;
        void update(const PointLightGL& light) noexcept;

    private:
        GLuint m_ubo;
        size_t m_next = 0;
        std::vector<GLuint> m_free;
    };
}