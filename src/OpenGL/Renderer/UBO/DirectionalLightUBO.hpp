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
    class DirectionalLightGL;

    class AXION_GL_API DirectionalLightUBO
    {
    private:
        struct DirectionalLightUBOData
        {
            Vector3f direction;
            float pad;
            Color3 color;
            float intensity;
        };

    public:
        DirectionalLightUBO();
        ~DirectionalLightUBO();

        void load(DirectionalLightGL& light) noexcept;
        void unload(DirectionalLightGL& light) noexcept;

        void updateLight(const DirectionalLightGL& light) noexcept;
        void updateDirections(IndexVector<DirectionalLightGL>& lights, const Matrix4f& view) noexcept;

    private:
        GLuint m_uboLights;

        IndexVector<DirectionalLightUBOData> m_directionalLights;
    };
}