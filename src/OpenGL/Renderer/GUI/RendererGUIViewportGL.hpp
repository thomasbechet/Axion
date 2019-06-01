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
        RendererGUIViewportGL(RenderContent& content, const Vector2u& rect, const Vector2u& resolution, RenderMode mode);
        ~RendererGUIViewportGL();

    public:
        void setRendermode(RenderMode mode) override;
        void setCamera(RendererCameraHandle camera) override;
        void setResolution(const Vector2u& resolution) override;
        void setViewport(const Rectu& rect) override;     

    public:
        void render(double alpha) const noexcept;
        RenderBuffer& getRenderBuffer() const noexcept;
        Rectu getViewport() const noexcept;

        void setID(Id id) noexcept;
        Id getID() const noexcept;

    private:
        Color3 m_clearColor = Color3(0.0f, 0.0f, 0.0f);
        Rectu m_viewport; 
        Vector2u m_resolution;

        std::unique_ptr<RenderPass> m_renderPass;
        std::unique_ptr<RenderBuffer> m_renderBuffer;
        RendererCameraGL* m_camera = nullptr;
        RenderContent& m_content;

        Id m_id;
    };
}