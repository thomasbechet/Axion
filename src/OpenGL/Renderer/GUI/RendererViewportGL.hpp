#pragma once

#include <OpenGL/Export.hpp>
#include <OpenGL/Renderer/RenderPass/RenderPass.hpp>
#include <Core/Utility/Types.hpp>
#include <Core/Utility/Color.hpp>
#include <Core/Renderer/GUI/RendererViewport.hpp>


#include <memory>

namespace ax
{
    class AXION_GL_API RendererViewportGL : public RendererViewport
    {
    public:
        Color3 clearColor = Color3(0.0f, 0.0f, 0.0f);

        Vector2u resolution = Vector2u(0, 0);
        Vector2f position = Vector2f(0.0f, 0.0f);
        Vector2f size = Vector2f(1.0f, 1.0f);

        std::unique_ptr<RenderPass> renderPass;
        Id camera = 0;

        Id id;
    };
}