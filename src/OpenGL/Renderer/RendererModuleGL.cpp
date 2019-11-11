#include <OpenGL/Renderer/RendererModuleGL.hpp>

#include <OpenGL/Renderer/Shader/ShaderConstants.hpp>
#include <Core/Context/Engine.hpp>
#include <Core/Window/WindowModule.hpp>
#include <Core/Logger/LoggerModule.hpp>
#include <Core/Asset/AssetModule.ipp>
#include <Core/Content/Asset/Package.hpp>
#include <Core/Renderer/RendererException.hpp>

#include <GL/glew.h>

#include <fstream>

using namespace ax;

void RendererModuleGL::initialize() noexcept
{
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
        Engine::interrupt("Failed to initialize GLEW");

    //Version information
    Engine::logger().log("GL version: " + std::string((const char*)glGetString(GL_VERSION)), Severity::Info);
    Engine::logger().log("GLSL version: " + std::string((const char*)glGetString(GL_SHADING_LANGUAGE_VERSION)), Severity::Info);

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
    if(USE_LIGHT_CULLING) m_content.cullLightSSBO = std::make_unique<CullLightSSBO>(Vector2u(1, 1));

    //Load shaders
    Package::Parameters packageParameters;
    packageParameters.source = "$ENGINE_DIR/packages/glsl_shaders_package.json";
    Engine::asset().load<Package>("glsl_shaders_package", packageParameters, true);
    m_content.debugLightCullingShader = Engine::asset().get<Shader>("glsl_debug_light_culling");
    m_content.geometryShader = Engine::asset().get<Shader>("glsl_geometry");
    m_content.genericShader = Engine::asset().get<Shader>("glsl_generic");
    m_content.postProcessShader = Engine::asset().get<Shader>("glsl_post_process");
    m_content.quadTextureShader = Engine::asset().get<Shader>("glsl_quad_texture");
    m_content.wireframeShader = Engine::asset().get<Shader>("glsl_wireframe");
    m_content.guiRectangleShader = Engine::asset().get<Shader>("glsl_gui_rectangle");

    //Compute shader
    if(USE_LIGHT_CULLING)
    {
        Path lightCullPath = "$ENGINE_DIR/shaders/glsl/light_culling.comp";
        std::ifstream lightCullFile(lightCullPath.str());
        if(!lightCullFile.is_open()) Engine::interrupt("Failed to load compute file: " + lightCullPath);
        std::string lightCullCode{std::istreambuf_iterator<char>(lightCullFile), std::istreambuf_iterator<char>()};
        if(!m_content.lightCullingComputeShader.loadCompute(lightCullCode))
            Engine::interrupt("Failed to load compute shader.");
    }

    //Specific content
    RendererShaderHandle quadTextureShaderHandle = m_content.quadTextureShader->getHandle();
    m_quadTextureShader = static_cast<RendererShaderGL&>(*quadTextureShaderHandle).shader.getProgram();
    RendererShaderHandle guiRectangleShaderHandle = m_content.guiRectangleShader->getHandle();
    m_guiRectangleShader = static_cast<RendererShaderGL&>(*guiRectangleShaderHandle).shader.getProgram();

    m_layout = std::make_unique<RendererGUILayoutGL>(
        m_guiRectangleShader,
        0
    );

    RendererGUIRectangleHandle rectangle1 = m_layout->createRectangle();
    Transform2D* trans = new Transform2D();
    trans->translate(Vector2f(20.0f, 30.0f));
    rectangle1->setTransform(trans);
    rectangle1->setColor(Color3(1.0f, 0.0f, 0.0f));
    rectangle1->setTexture(Engine::asset().get<Texture>("texture_image")->getHandle());
    rectangle1->setSize(Vector2u(300, 225));
    Rectu uv;
    uv.bottom = 0;
    uv.left = 0;
    uv.width = 300;
    uv.height = 225;
    rectangle1->setUV(uv);

    RendererGUIRectangleHandle rectangle2 = m_layout->createRectangle();
    trans = new Transform2D();
    trans->translate(Vector2f(270.0f, 30.0f));
    trans->rotate(30.0f);
    rectangle2->setTransform(trans);
    rectangle2->setColor(Color3(0.0f, 1.0f, 0.0f));
    rectangle2->setTexture(Engine::asset().get<Texture>("texture_image")->getHandle());
    rectangle2->setSize(Vector2u(300, 225));
    uv.bottom = 0;
    uv.left = 0;
    uv.width = 300;
    uv.height = 225;
    rectangle2->setUV(uv);

    //rectangle1->setDepth(1);
    rectangle2->setDepth(-1);
}
void RendererModuleGL::terminate() noexcept
{
    m_content.debugLightCullingShader.reset();
    m_content.geometryShader.reset();
    m_content.genericShader.reset();
    m_content.postProcessShader.reset();
    m_content.quadTextureShader.reset();
    m_content.wireframeShader.reset();
    m_content.guiRectangleShader.reset();
}
void RendererModuleGL::update(double alpha) noexcept
{
    for(auto& viewport : m_content.viewports)
    {
        viewport.get()->render(alpha);
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    glBindVertexArray(m_content.quadVAO);
    glUseProgram(m_quadTextureShader);
    for(auto& viewport : m_content.viewports)
    {
        Rectu rect = viewport->getViewport();
        glViewport(rect.left, rect.bottom, rect.width, rect.height);
        viewport->getRenderBuffer().bindForReading();
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    glBindVertexArray(0);

    Vector2u windowSize = Engine::window().getSize();
    glViewport(0, 0, windowSize.x, windowSize.y);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    m_layout->draw();
    glDisable(GL_BLEND);
}