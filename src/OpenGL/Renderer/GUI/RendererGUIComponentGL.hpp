#pragma once

#include <OpenGL/Export.hpp>

namespace ax
{
    class RendererGUILayoutGL;

    class AXION_GL_API RendererGUIComponentGL
    {
    public:
        RendererGUIComponentGL(RendererGUILayoutGL& layout);
        virtual ~RendererGUIComponentGL() = default;
        virtual void draw() noexcept = 0;

    protected:
        RendererGUILayoutGL& m_layout;
    };
}