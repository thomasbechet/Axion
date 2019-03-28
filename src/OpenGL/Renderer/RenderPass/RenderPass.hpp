#pragma once

#include <OpenGL/Export.hpp>

namespace ax
{
    class RenderContent;
    class Viewport;

    class AXION_GL_API RenderPass
    {
    public:
        RenderPass(RenderContent& content, Viewport& viewport);
        virtual ~RenderPass() = default;

        virtual void initialize() noexcept = 0;
        virtual void terminate() noexcept = 0;
        virtual void updateResolution() noexcept = 0;
        virtual void render(double alpha) noexcept = 0;

    protected:
        RenderContent& content;
        Viewport& viewport;
    };
}