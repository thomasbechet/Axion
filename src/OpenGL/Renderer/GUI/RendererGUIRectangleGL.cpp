#include <OpenGL/Renderer/GUI/RendererGUIRectangleGL.hpp>

#include <OpenGL/Renderer/Asset/RendererTextureGL.hpp>
#include <OpenGL/Renderer/Asset/RendererShaderGL.hpp>
#include <OpenGL/Renderer/Shader/ShaderConstants.hpp>
#include <OpenGL/Renderer/GUI/RendererGUILayoutGL.hpp>

#include <GL/glew.h>

#include <array>

using namespace ax;

RendererGUIRectangleGL::RendererGUIRectangleGL(RendererGUILayoutGL& layout, GLuint defaultShader) :
    RendererGUIComponentGL(layout), m_defaultShader(defaultShader)
{
    create();
}
RendererGUIRectangleGL::~RendererGUIRectangleGL()
{
    destroy();
}

void RendererGUIRectangleGL::setTransform(Transform2D* transform)
{
    m_transform = transform;
}
void RendererGUIRectangleGL::setVisible(bool toggle)
{
    m_visible = toggle;
}
void RendererGUIRectangleGL::setTransparency(float transparency)
{
    m_transparency = transparency;
}
void RendererGUIRectangleGL::setColor(Color3 color)
{
    m_color = color; 
}
void RendererGUIRectangleGL::setDepth(int depth)
{
    m_layout.changeDepthComponent(*this, depth);
}

void RendererGUIRectangleGL::setSize(Vector2u size)
{
    m_size = size;
    updatePositions();
}
void RendererGUIRectangleGL::setOrigin(Vector2i origin)
{
    m_origin = origin;
    updatePositions();
}
void RendererGUIRectangleGL::setUV(Rectu uv)
{   
    m_uv = uv;
    updateUVs();
}
void RendererGUIRectangleGL::setTexture(RendererTextureHandle texture)
{
    m_texture = texture;
}
void RendererGUIRectangleGL::setShader(RendererShaderHandle shader)
{
    m_shader = shader;
}

void RendererGUIRectangleGL::draw() noexcept
{
    if(m_transform && m_visible)
    {
        if(m_shader)
            glUseProgram(static_cast<RendererShaderGL&>(*m_shader).shader.getProgram());
        else
            glUseProgram(m_defaultShader);

        glUniformMatrix3fv(TRANSFORM_MATRIX_LOCATION, 1, GL_FALSE, m_transform->getWorldMatrix().data());
        Vector4f colorAndTransparency;
        colorAndTransparency.x = m_color.r;
        colorAndTransparency.y = m_color.g;
        colorAndTransparency.z = m_color.b;
        colorAndTransparency.w = 1.0f - m_transparency;
        glUniform4fv(GUI_COLOR_LOCATION, 1, (GLfloat*)&colorAndTransparency);
        glActiveTexture(GL_TEXTURE0 + GUI_TEXTURE_BINDING);
        glBindTexture(GL_TEXTURE_2D, static_cast<RendererTextureGL&>(*m_texture).texture);

        glBindVertexArray(m_vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}

void RendererGUIRectangleGL::create() noexcept
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    unsigned indices[] = {1, 0, 3, 3, 2, 1};

    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * 6, &indices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &m_positionVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_positionVBO);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(Vector2f), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &m_uvVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_uvVBO);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(Vector2f), (void*)0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void RendererGUIRectangleGL::destroy() noexcept
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_ibo);
    glDeleteBuffers(1, &m_positionVBO);
    glDeleteBuffers(1, &m_uvVBO);
}

void RendererGUIRectangleGL::updatePositions() noexcept
{
    Vector2f positions[4];

    //Positions
    positions[0] = Vector2f(
        -m_origin.x,
        -m_origin.y
    );
    positions[1] = Vector2f(
        -m_origin.x,
        -m_origin.y + m_size.y
    );
    positions[2] = Vector2f(
        -m_origin.x + m_size.x,
        -m_origin.y + m_size.y
    );
    positions[3] = Vector2f(
        -m_origin.x + m_size.x,
        -m_origin.y
    );

    glBindBuffer(GL_ARRAY_BUFFER, m_positionVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vector2f) * 4, &positions[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void RendererGUIRectangleGL::updateUVs() noexcept
{
    //UV
    if(m_texture)
    {
        Vector2f uvs[4];

        Vector2u size = static_cast<RendererTextureGL&>(*m_texture).size;
        uvs[0] = Vector2f(
            (float)m_uv.left / (float)size.x,
            (float)m_uv.bottom / (float)size.y
        );
        uvs[1] = Vector2f(
            (float)m_uv.left / (float)size.x,
            (float)(m_uv.bottom + m_uv.height) / (float)size.y
        );
        uvs[2] = Vector2f(
            (float)(m_uv.left + m_uv.width) / (float)size.x,
            (float)(m_uv.bottom + m_uv.height) / (float)size.y
        );
        uvs[3] = Vector2f(
            (float)(m_uv.left + m_uv.width) / (float)size.x,
            (float)m_uv.bottom / (float)size.y
        );

        glBindBuffer(GL_ARRAY_BUFFER, m_uvVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vector2f) * 4, &uvs[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}