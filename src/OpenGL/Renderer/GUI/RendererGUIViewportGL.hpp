#pragma once

#include <OpenGL/Export.hpp>
#include <OpenGL/Renderer/RenderPass/RenderPass.hpp>
#include <OpenGL/Renderer/Scene/RendererCameraGL.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Utility/Color.hpp>
#include <Core/Renderer/GUI/RendererGUIViewport.hpp>

#include <memory>

namespace ax
{
    class AXION_GL_API RendererGUIViewportGL : public RendererGUIViewport
    {
    public:
        void setRendermode(RenderMode mode) override;
        void setCamera(RendererCameraHandle camera) override;
        void setResolution(const Vector2u& resolution) override;
        void setRectangle(const Vector2f& position, const Vector2f& size) override;

        Color3 clearColor = Color3(0.0f, 0.0f, 0.0f);

        Vector2u resolution = Vector2u(0, 0);
        Vector2f position = Vector2f(0.0f, 0.0f);
        Vector2f size = Vector2f(1.0f, 1.0f);

        std::unique_ptr<RenderPass> renderPass;
        RendererCameraGL* camera = nullptr;

        RenderContent* content = nullptr;
        Id id;
    };
}