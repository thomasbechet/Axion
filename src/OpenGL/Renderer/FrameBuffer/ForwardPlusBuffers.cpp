#include <OpenGL/Renderer/FrameBuffer/ForwardPlusBuffers.hpp>

#include <Core/Context/Engine.hpp>

using namespace ax;

ForwardPlusBuffers::ForwardPlusBuffers(Vector2u dimensions)
{
    //GENERATE TEXTURES
    //Normal
    glGenTextures(1, &m_normalTexture);
    glBindTexture(GL_TEXTURE_2D, m_normalTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, dimensions.x, dimensions.y, 0, GL_RGB, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    //Depth Stencil
    glGenTextures(1, &m_depthTexture);
    glBindTexture(GL_TEXTURE_2D, m_depthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, dimensions.x, dimensions.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    //Light
    glGenTextures(1, &m_lightTexture);
    glBindTexture(GL_TEXTURE_2D, m_lightTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, dimensions.x, dimensions.y, 0, GL_RGB, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    

    //GENERATE FBO GEOMETRY
    glGenFramebuffers(1, &m_fboGeometry);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fboGeometry);
    
    glBindTexture(GL_TEXTURE_2D, m_normalTexture);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_normalTexture, 0);
    glBindTexture(GL_TEXTURE_2D, m_depthTexture);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture, 0);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(status != GL_FRAMEBUFFER_COMPLETE){
        Engine::interrupt("Failed to configure geometry buffer from ForwardPlusPass");
    }

    //GENERATE FBO LIGHT
    glGenFramebuffers(1, &m_fboLight);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fboLight);

    glBindTexture(GL_TEXTURE_2D, m_lightTexture);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_lightTexture, 0);
    glBindTexture(GL_TEXTURE_2D, m_depthTexture);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture, 0);

    status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(status != GL_FRAMEBUFFER_COMPLETE){
        Engine::interrupt("Failed to configure light buffer from ForwardPlusPass");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
ForwardPlusBuffers::~ForwardPlusBuffers()
{
    glDeleteFramebuffers(1, &m_fboGeometry);
    glDeleteFramebuffers(1, &m_fboLight);

    glDeleteTextures(1, &m_normalTexture);
    glDeleteTextures(1, &m_depthTexture);
    glDeleteTextures(1, &m_lightTexture);
}

void ForwardPlusBuffers::bindForGeometryPass() noexcept
{
    //Bind FBO GEOMETRY
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fboGeometry);
    GLenum buffers[] = 
    {
        GL_COLOR_ATTACHMENT0
    };
    glDrawBuffers(1, buffers);
}
void ForwardPlusBuffers::bindForCullPass() noexcept
{   
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_depthTexture);
}
void ForwardPlusBuffers::bindForLightPass() noexcept
{
    //Bind FBO LIGHT
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fboLight);
    GLenum buffers[] = 
    {
        GL_COLOR_ATTACHMENT0
    };
    glDrawBuffers(1, buffers);

    //Bind Textures
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, m_normalTexture);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, m_depthTexture);
}
void ForwardPlusBuffers::bindForPPPass() noexcept
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_lightTexture);
}
