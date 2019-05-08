#pragma once

#include <OpenGL/Export.hpp>
#include <OpenGL/Renderer/GUI/RendererGUIComponentGL.hpp>
#include <Core/Renderer/GUI/RendererGUILayout.hpp>
#include <Core/Utility/Types.hpp>

#include <GL/glew.h>

#include <memory>
#include <vector>

namespace ax
{
    class AXION_GL_API RendererGUILayoutGL : public RendererGUILayout
    {
    public:
        RendererGUILayoutGL(
            GLuint guiRectangleShader,
            GLuint guiScalableRectangleShader
        );

        RendererGUIRectangleHandle createRectangle() override;
        void destroyRectangle(RendererGUIRectangleHandle& handle) override;

        RendererGUIScalableRectangleHandle createScalableRectangle() override;
        void destroyScalableRectangle(RendererGUIScalableRectangleHandle& handle) override;

        void draw() noexcept;
    
    private:
        std::vector<std::pair<unsigned, std::unique_ptr<RendererGUIComponentGL>>> m_components;
        GLuint m_guiRectangleShader;
        GLuint m_guiScalableRectangleShader;
    };
}