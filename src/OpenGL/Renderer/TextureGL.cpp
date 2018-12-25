#include <OpenGL/Renderer/RendererGL.hpp>

using namespace ax;

//Texture
Id RendererGL::createTexture(
    Vector2u size,
    TextureFormat format,
    const Byte* data
)
{
    Id id = m_content.textures.add(TextureGL());
    TextureGL& texture = m_content.textures.get(id);

    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.id);

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

    return id;
}
void RendererGL::destroyTexture(Id id)
{
    TextureGL& texture = m_content.textures.get(id);
    glDeleteTextures(1, &texture.id);
    m_content.textures.remove(id);
}