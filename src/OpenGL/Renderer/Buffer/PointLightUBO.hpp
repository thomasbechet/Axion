#pragma once

#include <OpenGL/Export.hpp>
#include <Core/Utility/Color.hpp>
#include <Core/Utility/IndexVector.hpp>
#include <Core/Math/Matrix.hpp>

#include <GL/glew.h>

#include <vector>
#include <array>
#include <memory>

namespace ax
{
    class RendererPointLightGL;

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

        void load(RendererPointLightGL& light) noexcept;
        void unload(RendererPointLightGL& light) noexcept;

        void updateLight(const RendererPointLightGL& light) noexcept;
        void updateMemory(IndexVector<std::unique_ptr<RendererPointLightGL>>& lights, const Matrix4f& view) noexcept;

    private:
        GLuint m_uboLights;

        IndexVector<PointLightUBOData> m_pointlights;
    };
}