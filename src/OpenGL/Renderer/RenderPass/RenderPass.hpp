#pragma once

#include <OpenGL/Export.hpp>

namespace ax
{
    class RenderContent;
    class RendererViewportGL;

    class AXION_GL_API RenderPass
    {
    public:
        RenderPass(RenderContent& content, RendererViewportGL& viewport);
        virtual ~RenderPass() = default;

        virtual void initialize() noexcept = 0;
        virtual void terminate() noexcept = 0;
        virtual void updateResolution() noexcept = 0;
        virtual void render(double alpha) noexcept = 0;

    protected:
        RenderContent& content;
        RendererViewportGL& viewport;
    };
}