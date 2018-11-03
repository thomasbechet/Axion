#pragma once

///////////////
//HEADERS
///////////////
#include <OpenGL/Export.hpp>

namespace ax
{
    class RendererContent;

    class AXION_GL_API RenderPass
    {
    public:
        RendererPass(RendererContent& content);
        virtual ~RendererPass() = default;

        virtual void initialize() noexcept = 0;
        virtual void terminate() noexcept = 0;
        virtual void updateViewport() noexcept = 0;
        virtual void render(double alpha) noexcept = 0;

    protected:
        RendererContent& content;
    };
}