#include <OpenGL/Renderer/RendererGL.hpp>

using namespace ax;

//Texture
Id RendererGL::createTexture(
    Vector2u size,
    TextureFormat format,
    const Byte* data
)
{
    Id id = m_textures.add(RendererGL());
    TextureGL& texture = m_textures.get(id);

    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_TYPE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glGenerateMipmap(GL_TEXTURE_2D);

    return id;
}
void RendererGL::destroyTexture(Id id)
{
    TextureGL& texture = m_textures.get(id);
    glDeleteTextures(1, &texture.id);
    m_textures.remove(texture.id);
}