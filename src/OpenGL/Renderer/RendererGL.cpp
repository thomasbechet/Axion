#include <OpenGL/Renderer/RendererGL.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Window/Window.hpp>

#include <GL/glew.h>

using namespace ax;

void RendererGL::initialize() noexcept
{
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
        Engine::interrupt("Failed to initialize GLEW");

    //Generate fullscreen quad
    float vertices[] =
    {
        1.0f, 1.0f,
        -1.0f, 1.0f,
        -1.0f, -1.0f,
        1.0f, -1.0f,
        1.0f, 1.0f,
        -1.0f, -1.0f
    };

    glGenVertexArrays(1, &m_content.quadVAO);
    glBindVertexArray(m_content.quadVAO);

    glGenBuffers(1, &m_content.quadVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_content.quadVBO);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), &vertices, GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Initialize ubos
    m_content.materialUBO = std::make_unique<MaterialUBO>();
    m_content.pointLightUBO = std::make_unique<PointLightUBO>();

    //Initialize renderpass
    m_renderMode = RenderMode::Debug0;
    createRenderPass();
    m_renderPass->initialize();
}
void RendererGL::terminate() noexcept
{
    m_renderPass->terminate();
}
void RendererGL::update(double alpha) noexcept
{
    m_renderPass->render(alpha);
}

//Viewport
void RendererGL::updateViewport() noexcept
{
    m_content.windowSize = Engine::window().getSize();
    if(m_renderPass) m_renderPass->updateViewport();
}

//Rendermode
void RendererGL::setRenderMode(RenderMode mode)
{
    m_renderPass->terminate();

    m_renderMode = mode;
    createRenderPass();

    m_renderPass->initialize();  
}
RenderMode RendererGL::getRenderMode()
{
    return m_renderMode;
}

void RendererGL::createRenderPass() noexcept
{
    m_renderPass.reset();
    switch(m_renderMode)
    {
        case RenderMode::Default:
            m_renderPass = std::make_unique<DefaultPass>(m_content);
        break;
        case RenderMode::Wireframe:
            m_renderPass = std::make_unique<WireframePass>(m_content);
        break;
        case RenderMode::Debug0:
            m_renderPass = std::make_unique<DebugPass>(m_content);
        break;
        case RenderMode::Debug1:
            m_renderPass = std::make_unique<DebugPass>(m_content);
        break;
        case RenderMode::Debug2:
            m_renderPass = std::make_unique<DebugPass>(m_content);
        break;
        default:
            m_renderPass = std::make_unique<DefaultPass>(m_content);
        break;
    }
}