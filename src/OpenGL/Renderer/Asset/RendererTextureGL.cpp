#include <OpenGL/Renderer/Asset/RendererTextureGL.hpp>
#include <OpenGL/Renderer/RendererGL.hpp>

using namespace ax;

RendererTextureHandle RendererGL::createTexture(Vector2u size, TextureFormat format, const Byte* data)
{
    Id id = m_content.textures.add(std::make_unique<RendererTextureGL>());
    RendererTextureGL* texture = m_content.textures.get(id).get();
    texture->id = id;

    texture->size = size;

    glGenTextures(1, &texture->texture);
    glBindTexture(GL_TEXTURE_2D, texture->texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    if(format == TextureFormat::RGB)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    else if(format == TextureFormat::RGBA)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    else if(format == TextureFormat::R)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, size.x, size.y, 0, GL_RED, GL_UNSIGNED_BYTE, data);
    }

    glGenerateMipmap(GL_TEXTURE_2D);

    return texture;
}
void RendererGL::destroyTexture(RendererTextureHandle& texturePointer)
{
    RendererTextureGL* texture = static_cast<RendererTextureGL*>(texturePointer);
    glDeleteTextures(1, &texture->id);
    m_content.textures.remove(texture->id);
    texturePointer = nullptr;
}