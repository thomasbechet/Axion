#pragma once

///////////////
//HEADERS
///////////////
#include <OpenGL/Export.hpp>

namespace ax
{
    class RenderContent;

    class AXION_GL_API RenderPass
    {
    public:
        RenderPass(RenderContent& content);
        virtual ~RenderPass() = default;

        virtual void initialize() noexcept = 0;
        virtual void terminate() noexcept = 0;
        virtual void updateViewport() noexcept = 0;
        virtual void render(double alpha) noexcept = 0;

    protected:
        RenderContent& content;
    };
}