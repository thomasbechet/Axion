#pragma once

#include <OpenGL/Export.hpp>

namespace ax
{
    class AXION_GL_API RendererGUIComponentGL
    {
    public:
        virtual ~RendererGUIComponentGL() = default;
        virtual void draw() noexcept = 0;
    };
}