#pragma once

//////////////
//HEADERS
//////////////
#include <OpenGL/Export.hpp>
#include <OpenGL/Renderer/UBO/UBOConstants.hpp>
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

        void updatePositions(IndexVector<PointLightGL>& lights, const Matrix4f& view) noexcept;
        void updateIndexes() noexcept;
        void updateLight(const PointLightGL& light) noexcept;

    private:
        GLuint m_uboLights;
        GLuint m_uboIndexes;
        std::vector<GLuint> m_free;

        std::vector<GLuint> m_indexes;
        std::array<PointLightUBOData, POINTLIGHT_MAX_NUMBER> m_pointlights;
    };
}