#include <OpenGL/Renderer/GBuffer.hpp>

#include <Core/Context/Engine.hpp>

using namespace ax;

GBuffer::GBuffer(Vector2u dimensions)
{
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);

    //Albedo
    glGenTextures(1, &m_albedoTexture);
    glBindTexture(GL_TEXTURE_2D, m_albedoTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, dimensions.x, dimensions.y, 0, GL_RGB, GL_FLOAT, nullptr);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_albedoTexture, 0);

    //Normal
    glGenTextures(1, &m_normalTexture);
    glBindTexture(GL_TEXTURE_2D, m_normalTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, dimensions.x, dimensions.y, 0, GL_RGB, GL_FLOAT, nullptr);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_normalTexture, 0);

    //Position
    glGenTextures(1, &m_positionTexture);
    glBindTexture(GL_TEXTURE_2D, m_positionTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, dimensions.x, dimensions.y, 0, GL_RGB, GL_FLOAT, nullptr);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_positionTexture, 0);

    //Depth
    glGenTextures(1, &m_depthTexture);
    glBindTexture(GL_TEXTURE_2D, m_depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, dimensions.x, dimensions.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture, 0);

    GLenum DrawBuffers[] = {
        GL_COLOR_ATTACHMENT0, 
        GL_COLOR_ATTACHMENT1, 
        GL_COLOR_ATTACHMENT2, 
        GL_COLOR_ATTACHMENT3
    };
    glDrawBuffers(4, DrawBuffers);

    GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (Status != GL_FRAMEBUFFER_COMPLETE) {
        Engine::interrupt("Failed to load gbuffer");
    }

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}
GBuffer::~GBuffer()
{
    glDeleteFramebuffers(1, &m_fbo);

    glDeleteTextures(1, &m_albedoTexture);
    glDeleteTextures(1, &m_normalTexture);
    glDeleteTextures(1, &m_positionTexture);
    glDeleteTextures(1, &m_depthTexture);
}

void GBuffer::bindForWriting() noexcept
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
}
void GBuffer::bindForReading() noexcept
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);
}

