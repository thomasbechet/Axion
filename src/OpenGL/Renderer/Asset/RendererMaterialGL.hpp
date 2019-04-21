#pragma once

#include <OpenGL/Export.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Renderer/Asset/RendererMaterial.hpp>

#include <GL/glew.h>

namespace ax
{
    class RenderContent;

    class AXION_GL_API RendererMaterialGL : public RendererMaterial
    {
    public:
        void update(const RendererMaterialParameters& settings) override;

        RendererMaterialParameters parameters;
        GLuint uboIndex;

        RenderContent* content = nullptr;
        Id id;
    };
}