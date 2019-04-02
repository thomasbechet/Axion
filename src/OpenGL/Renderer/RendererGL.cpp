#include <OpenGL/Renderer/RendererGL.hpp>

#include <OpenGL/Renderer/RenderPass/ForwardPlusPass.hpp>
#include <OpenGL/Renderer/RenderPass/WireframePass.hpp>
#include <OpenGL/Renderer/RenderPass/DebugLightCullingPass.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/Window/Window.hpp>
#include <Core/Asset/AssetManager.hpp>

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

    for(auto& viewport : m_viewports)
    {
        viewport.get()->renderPass->terminate();
    }
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

RendererCameraHandle RendererGL::createCamera()
{
    Id id = m_content.cameras.add(std::make_unique<RendererCameraGL>());
    RendererCameraGL* camera = m_content.cameras.get(id);
    camera->id = id;

    return camera;
}
void RendererGL::destroyCamera(RendererCameraHandle& cameraPointer)
{
    RendererCameraGL* camera = static_cast<RendererCameraGL*>(cameraPointer);
    m_content.cameras.remove(camera->id);
    cameraPointer = nullptr;
}

RendererStaticmeshHandle RendererGL::createStaticmesh()
{
    Id id = m_staticmesh.add(std::make_unique<RendererStaticmeshGL>());
    RendererStaticmeshGL* staticmesh = m_staticmesh.get(id).get();
    staticmesh->id = id;
    staticmesh->content = m_content;
    
    return staticmesh;
}
void RendererGL::destroyStaticmesh(RendererStaticmeshHandle& staticmeshPointer)
{
    RendererStaticmeshGL* staticmesh = static_cast<RendererStaticmeshGL*>(staticmeshPointer);
    staticmesh->setMaterial(nullptr);
    Id id = staticmesh->id;
    m_content.staticmeshes.remove(id);
    staticmeshPointer = nullptr;
}

RendererPointLightHandle RendererGL::createPointLight()
{
    Id id = m_content.pointLights.add(std::make_unique<RendererPointLightGL>());
    RendererPointLightGL* pointLight = *m_content.pointLights.get(id);
    pointLight->id = id;
    pointLight->content = m_content;

    m_content.pointLightUBO->load(light);
    m_content.pointLightUBO->updateLight(light);

    return pointLight;
}
void RendererGL::destroyPointLight(RendererPointLightHandle& pointlightPointer)
{
    RendererPointLightGL* pointLight = static_cast<RendererPointLightGL*>(pointLightPointer);
    m_content.pointLightUBO->unload(pointLight);
    m_content.pointLights.remove(pointLight->id);

    pointlightPointer = nullptr;
}

RendererDirectionalLightHandle RendererGL::createDirectionalLight()
{
    Id id = m_content.directionalLights.add(std::make_unique<RendererDirectionalLightGL>());
    RendererDirectionalLightGL* directionalLight = *m_content.directionalLights.get(id).get();
    directionalLight->id = id;
    directionalLight->content = &m_content;

    m_content.directionalLightUBO->load(directionalLight);
    //m_content.pointLightUBO->updateLight(directionalLight);

    return directionalLight;
}
void RendererGL::destroyDirectionalLight(RendererDirectionalLightHandle& directionallightPointer)
{
    RendererDirectionalLightGL* directionalLight = static_cast<RendererDirectionalLightGL*>(directionallightPointer);
    m_content.directionalLightUBO->unload(directionalLight);
    m_content.directionalLights.remove(directionalLight->id);

    directionallightPointer = nullptr;
}

Id RendererGL::createViewport(const Vector2f& position, const Vector2f& size, RenderMode mode)
{
    Id id = m_viewports.add(std::make_unique<Viewport>());
    Viewport& viewport = *m_viewports.get(id).get();

    viewport.position = position;
    viewport.size = size;
    viewport.resolution = Engine::window().getSize();

    m_content.cullLightSSBO->setResolution(viewport.resolution);
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
        case RenderMode::Debug0:
            viewport.renderPass = std::make_unique<DebugLightCullingPass>(m_content, viewport);
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
    m_content.cullLightSSBO->setResolution(viewport.resolution);
    viewport.renderPass->updateResolution();
}
void RendererGL::setViewportRectangle(Id id, const Vector2f& position, const Vector2f& size)
{
    Viewport& viewport = *m_viewports.get(id).get();

    viewport.position = position;
    viewport.size = size;
}