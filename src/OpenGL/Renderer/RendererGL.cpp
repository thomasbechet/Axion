#include <OpenGL/Renderer/RendererGL.hpp>

#include <OpenGL/Renderer/RenderPass/ForwardPlusPass.hpp>
#include <OpenGL/Renderer/RenderPass/WireframePass.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Window/Window.hpp>
#include <Core/Asset/AssetManager.hpp>

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
    m_content.cameraUBO = std::make_unique<CameraUBO>();
    m_content.pointLightUBO = std::make_unique<PointLightUBO>();
    m_content.directionalLightUBO = std::make_unique<DirectionalLightUBO>();

    //Load shaders
    AssetReference<Shader> shader;
    shader = Engine::assets().shader.create("renderergl_shader_quadrender",
        "../shaders/quad_texture.vert",
        "../shaders/quad_texture.frag");
    if(shader->isLoaded())
        m_content.quadRenderShader = m_content.shaders.get(shader->getHandle()).programId;
    else
        Engine::interrupt("Failed to load shader: renderergl_shader_quadrender");
}
void RendererGL::terminate() noexcept
{
    for(auto& viewport : m_viewports)
    {
        viewport.get()->renderPass->terminate();
    }

    Engine::assets().shader.destroy("renderergl_shader_quadrender");
}
void RendererGL::update(double alpha) noexcept
{
    for(auto& viewport : m_viewports)
    {
        if(viewport.get()->camera)
        {
            viewport.get()->renderPass->render(alpha);
        }
    }
}

Id RendererGL::createViewport(const Vector2f& position, const Vector2f& size, RenderMode mode)
{
    Id id = m_viewports.add(std::make_unique<Viewport>());
    Viewport& viewport = *m_viewports.get(id).get();

    viewport.position = position;
    viewport.size = size;
    viewport.resolution = Engine::window().getSize();

    setViewportRendermode(id, mode);

    return id;
}
void RendererGL::destroyViewport(Id id)
{
    Viewport& viewport = *m_viewports.get(id).get();

    viewport.renderPass->terminate();

    m_viewports.remove(id);
}
void RendererGL::setViewportRendermode(Id id, RenderMode mode)
{
    Viewport& viewport = *m_viewports.get(id).get();

    if(viewport.renderPass) viewport.renderPass->terminate();
    viewport.renderPass.reset();

    switch(mode)
    {
        case RenderMode::Default:
            viewport.renderPass = std::make_unique<ForwardPlusPass>(m_content, viewport);
        break;
        case RenderMode::ForwardPlusShading:
            viewport.renderPass = std::make_unique<ForwardPlusPass>(m_content, viewport);
        break;
        case RenderMode::Wireframe:
            viewport.renderPass = std::make_unique<WireframePass>(m_content, viewport);
        break;
        default:
            viewport.renderPass = std::make_unique<ForwardPlusPass>(m_content, viewport);
        break;
    }
    
    viewport.renderPass->initialize();
}
void RendererGL::setViewportCamera(Id id, Id camera)
{
    Viewport& viewport = *m_viewports.get(id).get();

    viewport.camera = camera;
}
void RendererGL::setViewportResolution(Id id, const Vector2u& resolution)
{
    Viewport& viewport = *m_viewports.get(id).get();

    viewport.resolution = resolution;
    viewport.renderPass->updateResolution();
}
void RendererGL::setViewportRectangle(Id id, const Vector2f& position, const Vector2f& size)
{
    Viewport& viewport = *m_viewports.get(id).get();

    viewport.position = position;
    viewport.size = size;
}