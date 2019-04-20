#include <OpenGL/Renderer/RendererGL.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Window/Window.hpp>
#include <Core/Asset/AssetManager.hpp>
#include <Core/Renderer/RendererException.hpp>

#include <GL/glew.h>

#include <fstream>

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

    //Initialize buffers
    m_content.materialUBO = std::make_unique<MaterialUBO>();
    m_content.cameraUBO = std::make_unique<CameraUBO>();
    m_content.pointLightUBO = std::make_unique<PointLightUBO>();
    m_content.directionalLightUBO = std::make_unique<DirectionalLightUBO>();
    m_content.constantsUBO = std::make_unique<ConstantsUBO>();
    m_content.cullLightSSBO = std::make_unique<CullLightSSBO>(Vector2u(1, 1));

    //Load shaders
    Engine::assets().package.loadFromFile("shaders_package", "$ENGINE_DIR/packages/opengl_shaders_package.json");
    m_content.debugLightCullingShader = Engine::assets().shader("opengl_debug_light_culling");
    m_content.geometryShader = Engine::assets().shader("opengl_geometry");
    m_content.genericShader = Engine::assets().shader("opengl_generic");
    m_content.postProcessShader = Engine::assets().shader("opengl_post_process");
    m_content.quadTextureShader = Engine::assets().shader("opengl_quad_texture");
    m_content.wireframeShader = Engine::assets().shader("opengl_wireframe");
    
    //Compute shaders
    Path lightCullPath = "$ENGINE_DIR/shaders/glsl/light_culling.comp";
    std::ifstream lightCullFile(lightCullPath.path());
    if(!lightCullFile.is_open()) Engine::interrupt("Failed to load compute file: " + lightCullPath);
    std::string lightCullCode{std::istreambuf_iterator<char>(lightCullFile), std::istreambuf_iterator<char>()};
    if(!m_content.lightCullingComputeShader.loadCompute(lightCullCode))
        Engine::interrupt("Failed to load compute shader.");
}
void RendererGL::terminate() noexcept
{
    m_content.debugLightCullingShader.reset();
    m_content.geometryShader.reset();
    m_content.genericShader.reset();
    m_content.postProcessShader.reset();
    m_content.quadTextureShader.reset();
    m_content.wireframeShader.reset();

    for(auto& viewport : m_content.viewports)
    {
        viewport.get()->renderPass->terminate();
    }
}
void RendererGL::update(double alpha) noexcept
{
    for(auto& viewport : m_content.viewports)
    {
        if(viewport.get()->camera)
        {
            viewport.get()->renderPass->render(alpha);
        }
    }
}