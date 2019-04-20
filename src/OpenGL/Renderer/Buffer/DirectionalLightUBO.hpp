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
    class RendererDirectionalLightGL;

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

        void load(RendererDirectionalLightGL& light) noexcept;
        void unload(RendererDirectionalLightGL& light) noexcept;

        void updateLight(const RendererDirectionalLightGL& light) noexcept;
        void updateMemory(IndexVector<std::unique_ptr<RendererDirectionalLightGL>>& lights, const Matrix4f& view) noexcept;

    private:
        GLuint m_uboLights;

        IndexVector<DirectionalLightUBOData> m_directionalLights;
    };
}