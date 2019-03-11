#pragma once

//////////////
//HEADERS
//////////////
#include <OpenGL/Export.hpp>
#include <Core/Utility/Color.hpp>
#include <Core/Utility/IndexVector.hpp>
#include <Core/Math/Matrix.hpp>

#include <GL/glew.h>

#include <vector>
#include <array>

namespace ax
{
    class PointLightGL;

    class AXION_GL_API PointLightUBO
    {
    private:
        struct PointLightUBOData
        {
            Vector3f position;
            float radius;
            Color3 color;
            float intensity;
        };

    public:
        PointLightUBO();
        ~PointLightUBO();

        void load(PointLightGL& light) noexcept;
        void unload(PointLightGL& light) noexcept;

        void updateLight(const PointLightGL& light) noexcept;
        void updateMemory(IndexVector<PointLightGL>& lights, const Matrix4f& view) noexcept;

    private:
        GLuint m_uboLights;

        IndexVector<PointLightUBOData> m_pointlights;
    };
}