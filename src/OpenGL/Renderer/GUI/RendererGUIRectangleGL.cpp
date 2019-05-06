#include <OpenGL/Renderer/GUI/RendererGUIRectangleGL.hpp>

#include <OpenGL/Renderer/Asset/RendererTextureGL.hpp>
#include <GL/glew.h>

#include <array>

using namespace ax;

RendererGUIRectangleGL::RendererGUIRectangleGL()
{
    create();
}
RendererGUIRectangleGL::~RendererGUIRectangleGL()
{
    destroy();
}

void RendererGUIRectangleGL::setTransform(Transform2D* trans)
{
    transform = trans;
}
void RendererGUIRectangleGL::setVisible(bool toggle)
{
    visible = toggle;
}
void RendererGUIRectangleGL::setTransparency(float trans)
{
    transparency = trans;
}
void RendererGUIRectangleGL::setColor(Color3 color)
{
    //color = 
}
void RendererGUIRectangleGL::setDepth(unsigned depth)
{
    
}
void RendererGUIRectangleGL::setParameters(const RendererGUIRectangleParameters& params)
{
    parameters = params;
    update();
}

void RendererGUIRectangleGL::draw() noexcept
{
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void RendererGUIRectangleGL::create() noexcept
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned indices[] = {1, 0, 3, 3, 2, 1};

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * 6, &indices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &positionsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(Vector2f), (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &uvsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, uvsVBO);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(Vector2f), (void*)0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    update();
}
void RendererGUIRectangleGL::update() noexcept
{
    Vector2f positions[4];

    //Positions
    positions[0] = Vector2f(
        -parameters.origin.x,
        -parameters.origin.y
    );
    positions[1] = Vector2f(
        -parameters.origin.x,
        -parameters.origin.y + parameters.size.y
    );
    positions[2] = Vector2f(
        -parameters.origin.x + parameters.size.x,
        -parameters.origin.y + parameters.size.y
    );
    positions[3] = Vector2f(
        -parameters.origin.x + parameters.size.x,
        -parameters.origin.y
    );

    glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vector2f) * 4, &positions[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //UV
    if(parameters.texture)
    {
        Vector2f uvs[4];

        Vector2u size = static_cast<RendererTextureGL&>(*parameters.texture).size;
        uvs[0] = Vector2f(
            (float)parameters.uv.left / (float)size.x,
            (float)parameters.uv.bottom / (float)size.y
        );
        uvs[1] = Vector2f(
            (float)parameters.uv.left / (float)size.x,
            (float)(parameters.uv.bottom + parameters.uv.height) / (float)size.y
        );
        uvs[2] = Vector2f(
            (float)(parameters.uv.left + parameters.uv.width) / (float)size.x,
            (float)(parameters.uv.bottom + parameters.uv.height) / (float)size.y
        );
        uvs[3] = Vector2f(
            (float)(parameters.uv.left + parameters.uv.width) / (float)size.x,
            (float)parameters.uv.bottom / (float)size.y
        );

        glBindBuffer(GL_ARRAY_BUFFER, uvsVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vector2f) * 4, &uvs[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
void RendererGUIRectangleGL::destroy() noexcept
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &ibo);
    glDeleteBuffers(1, &positionsVBO);
    glDeleteBuffers(1, &uvsVBO);
}