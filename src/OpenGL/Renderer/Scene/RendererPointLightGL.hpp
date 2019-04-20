#pragma once

#include <OpenGL/Export.hpp>
#include <Core/Utility/Color.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Renderer/Scene/RendererPointLight.hpp>

#include <GL/glew.h>

namespace ax
{
    class Transform;
    class RenderContent;

    class AXION_GL_API RendererPointLightGL : public RendererPointLight
    {
    public:
        void setTransform(Transform* transform) override;
        void setParameters(const RendererPointLightParameters& parameters) override;

        Transform* transform = nullptr;

        Color3 color;
        float radius;
        float intensity;

        GLuint uboIndex;

        Id id;
        RenderContent* content = nullptr;
    };
}