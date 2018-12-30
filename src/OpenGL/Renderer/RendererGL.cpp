#include <OpenGL/Renderer/RendererGL.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Window/Window.hpp>
#include <Core/Assets/AssetManager.hpp>

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

    //Loading shaders
    Id handle = Engine::assets().shader.create("renderergl_shader_geometry",
        "../shaders/geometry_pass.vertex",
        "../shaders/geometry_pass.fragment")->getHandle();
    m_content.geometryShader = m_content.shaders.get(handle).programId;

    handle = Engine::assets().shader.create("renderergl_shader_light",
        "../shaders/light_pass.vertex",
        "../shaders/light_pass.fragment")->getHandle();
    m_content.lightShader = m_content.shaders.get(handle).programId;

    handle = Engine::assets().shader.create("renderergl_shader_render",
        "../shaders/quad_texture.vertex",
        "../shaders/quad_texture.fragment")->getHandle();
    m_content.renderShader = m_content.shaders.get(handle).programId;

    handle = Engine::assets().shader.create("renderergl_shader_wireframe",
        "../shaders/wireframe.vertex",
        "../shaders/wireframe.fragment")->getHandle();
    m_content.wireframeShader = m_content.shaders.get(handle).programId;

    handle = Engine::assets().shader.create("renderergl_shader_geometry_debug",
        "../shaders/geometry_debug.vertex",
        "../shaders/geometry_debug.fragment")->getHandle();
    m_content.debugShader = m_content.shaders.get(handle).programId;
}
void RendererGL::terminate() noexcept
{
    for(auto& viewport : m_viewports)
    {
        viewport.get()->renderPass->terminate();
    }

    Engine::assets().shader.destroy("renderergl_shader_geometry");
    Engine::assets().shader.destroy("renderergl_shader_light");
    Engine::assets().shader.destroy("renderergl_shader_render");
    Engine::assets().shader.destroy("renderergl_shader_wireframe");
    Engine::assets().shader.destroy("renderergl_shader_geometry_debug");
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
            viewport.renderPass = std::make_unique<DefaultPass>(m_content, viewport);
        break;
        case RenderMode::Wireframe:
            viewport.renderPass = std::make_unique<WireframePass>(m_content, viewport);
        break;
        case RenderMode::Debug0:
            viewport.renderPass = std::make_unique<DebugPass>(m_content, viewport);
        break;
        case RenderMode::Debug1:
            viewport.renderPass = std::make_unique<DebugPass>(m_content, viewport);
        break;
        case RenderMode::Debug2:
            viewport.renderPass = std::make_unique<DebugPass>(m_content, viewport);
        break;
        default:
            viewport.renderPass = std::make_unique<DefaultPass>(m_content, viewport);
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