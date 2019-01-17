#include <OpenGL/Renderer/RenderPass/ForwardPlusPass.hpp>

#include <OpenGL/Renderer/RendererGL.hpp>
#include <Core/Context/Engine.hpp>
#include <Core/Window/Window.hpp>
#include <Core/Asset/AssetManager.hpp>
#include <Core/Asset/Shader.hpp>

using namespace ax;

ForwardPlusPass::ForwardPlusPass(RenderContent& content, Viewport& viewport) : RenderPass(content, viewport) {}

void ForwardPlusPass::initialize() noexcept
{
    m_renderBuffer = std::make_unique<RenderBuffer>(viewport.resolution);
    m_buffers = std::make_unique<ForwardPlusBuffers>(viewport.resolution);

    m_cullingShader = std::make_unique<ComputeShader>(Path("../shaders/FP_light_culling.comp"));

    //Load shaders
    AssetReference<Shader> shader;

    shader = Engine::assets().shader.create("renderergl_shader_phong",
        "../shaders/FP_phong.vert",
        "../shaders/FP_phong.frag");
    if(shader->isLoaded())
        m_phongShader = content.shaders.get(shader->getHandle()).programId;
    else
        Engine::interrupt("Failed to load shader: renderergl_shader_phong");

    shader = Engine::assets().shader.create("renderergl_shader_geometry",
        "../shaders/FP_geometry.vert",
        "../shaders/FP_geometry.frag");
    if(shader->isLoaded())
        m_geometryShader = content.shaders.get(shader->getHandle()).programId;
    else
        Engine::interrupt("Failed to load shader: renderergl_shader_geometry");

    //Phong locations
    phongLocations.transform = glGetUniformLocation(m_phongShader, "transform");
    phongLocations.mvp = glGetUniformLocation(m_phongShader, "mvp");
    phongLocations.normalToView = glGetUniformLocation(m_phongShader, "normal_to_view");

    phongLocations.materialIndex = glGetUniformLocation(m_phongShader, "material_index");
    phongLocations.diffuseTexture = glGetUniformLocation(m_phongShader, "diffuse_texture");
    phongLocations.normalTexture = glGetUniformLocation(m_phongShader, "normal_texture");

    //Geometry locations
    geometryLocations.transform = glGetUniformLocation(m_geometryShader, "transform");
    geometryLocations.mvp = glGetUniformLocation(m_geometryShader, "mvp");
    geometryLocations.normalToView = glGetUniformLocation(m_geometryShader, "normal_to_view");

    geometryLocations.materialIndex = glGetUniformLocation(m_geometryShader, "material_index");
    geometryLocations.normalTexture = glGetUniformLocation(m_geometryShader, "normal_texture");
}
void ForwardPlusPass::terminate() noexcept
{
    //Unload buffers
    m_cullingShader.reset();
    m_buffers.reset();
    m_renderBuffer.reset();

    //Unload shaders
    Engine::assets().shader.destroy("renderergl_shader_phong");
    Engine::assets().shader.destroy("renderergl_shader_geometry");
}
void ForwardPlusPass::updateResolution() noexcept
{
    m_renderBuffer.reset(new RenderBuffer(viewport.resolution));
    m_buffers.reset(new ForwardPlusBuffers(viewport.resolution));
}
void ForwardPlusPass::render(double alpha) noexcept
{
    updateUBOs();
    renderGeometryPass();
    renderLightPass();
    renderPPPass();
    renderViewportPass();
}

void ForwardPlusPass::updateUBOs() noexcept
{
    //Compute camera matrix
    CameraGL& camera = content.cameras.get(viewport.camera);

    Vector3f eye = camera.transform->getTranslation();
    Vector3f target = camera.transform->getTranslation() + camera.transform->getForwardVector();
    Vector3f up = camera.transform->getUpVector();

    m_viewMatrix = Matrix4f::lookAt(eye, target, up);

    float aspect = (viewport.size.x * (float)Engine::window().getSize().x) /
        (viewport.size.y * (float)Engine::window().getSize().y);

    Matrix4f projectionMatrix = Matrix4f::perspective(camera.fov, aspect, camera.near, camera.far);

    m_vpMatrix = projectionMatrix * m_viewMatrix;

    //Updates Lights
    content.pointLightUBO->updatePositions(content.pointLights, m_viewMatrix);
    content.cameraUBO->update(m_viewMatrix, projectionMatrix);
}
void ForwardPlusPass::renderGeometryPass() noexcept
{
    //Viewport setup
    glViewport(0, 0, viewport.resolution.x, viewport.resolution.y);

    //Maybe useless configuration ?
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    //Render geometry
    glDepthMask(GL_TRUE); 
    glDepthFunc(GL_LESS);

    glUseProgram(m_geometryShader);
    m_buffers->bindForGeometryPass();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(auto& materialIt : content.materials)
    {
        MaterialGL& material = materialIt.first;

        glUniform1ui(geometryLocations.materialIndex, material.uboIndex);

        if(material.useNormalTexture)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, content.textures.get(material.normalTexture).id);
        }

        for(auto& staticmeshId : materialIt.second)
        {
            StaticmeshGL& staticmesh = content.staticmeshes.get(staticmeshId);
            if(staticmesh.mesh)
            {
                MeshGL& mesh = content.meshes.get(staticmesh.mesh);

                Matrix4f transform = staticmesh.transform->getWorldMatrix();
                Matrix4f mvp = m_vpMatrix * transform;
                Matrix3f normalToView = Matrix3f(m_viewMatrix) * Matrix3f::transpose(Matrix3f::inverse(Matrix3f(transform)));

                glUniformMatrix4fv(geometryLocations.transform, 1, GL_FALSE, transform.data());
                glUniformMatrix4fv(geometryLocations.mvp, 1, GL_FALSE, mvp.data());
                glUniformMatrix3fv(geometryLocations.normalToView, 1, GL_FALSE, normalToView.data());

                glBindVertexArray(mesh.vao);
                glDrawArrays(GL_TRIANGLES, 0, mesh.size);
                glBindVertexArray(0);
            }
        }
    }
}
void ForwardPlusPass::renderLightPass() noexcept
{
    //Draw scene
    glDepthMask(GL_FALSE); 
    glDepthFunc(GL_EQUAL);

    m_buffers->bindForLightPass();    
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(m_phongShader);
    for(auto& materialIt : content.materials)
    {
        MaterialGL& material = materialIt.first;

        glUniform1ui(phongLocations.materialIndex, material.uboIndex);

        if(material.useDiffuseTexture)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, content.textures.get(material.diffuseTexture).id);
        }

        if(material.useNormalTexture)
        {
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, content.textures.get(material.normalTexture).id);
        }

        for(auto& staticmeshId : materialIt.second)
        {
            StaticmeshGL& staticmesh = content.staticmeshes.get(staticmeshId);
            if(staticmesh.mesh)
            {
                MeshGL& mesh = content.meshes.get(staticmesh.mesh);

                Matrix4f transform = staticmesh.transform->getWorldMatrix();
                Matrix4f mvp = m_vpMatrix * transform;
                Matrix3f normalToView = Matrix3f(m_viewMatrix) * Matrix3f::transpose(Matrix3f::inverse(Matrix3f(transform)));

                glUniformMatrix4fv(phongLocations.transform, 1, GL_FALSE, transform.data());
                glUniformMatrix4fv(phongLocations.mvp, 1, GL_FALSE, mvp.data());
                glUniformMatrix3fv(phongLocations.normalToView, 1, GL_FALSE, normalToView.data());

                glBindVertexArray(mesh.vao);
                glDrawArrays(GL_TRIANGLES, 0, mesh.size);
                glBindVertexArray(0);
            }
        }
    }
}
void ForwardPlusPass::renderPPPass() noexcept
{
    glUseProgram(content.quadRenderShader);

    m_renderBuffer->bindForWriting();
    m_buffers->bindForPPPass();

    glDisable(GL_DEPTH_TEST);
    glBindVertexArray(content.quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
void ForwardPlusPass::renderViewportPass() noexcept
{
    //Render texture to backbuffer
    Vector2u windowSize = Engine::window().getSize();
    Vector2u position = Vector2u(
        (unsigned)((float)windowSize.x * viewport.position.x),
        (unsigned)((float)windowSize.y * viewport.position.y)
    );
    Vector2u size = Vector2u(
        (unsigned)((float)windowSize.x * viewport.size.x),
        (unsigned)((float)windowSize.y * viewport.size.y)
    );
    glViewport(position.x, position.y, size.x, size.y);

    glUseProgram(content.quadRenderShader);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    m_renderBuffer->bindForReading();

    glBindVertexArray(content.quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    glEnable(GL_DEPTH_TEST);

    glUseProgram(0);
}