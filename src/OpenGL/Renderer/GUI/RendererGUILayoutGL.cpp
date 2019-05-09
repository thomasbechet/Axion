#include <OpenGL/Renderer/GUI/RendererGUILayoutGL.hpp>
#include <OpenGL/Renderer/RendererGL.hpp>

#include <OpenGL/Renderer/GUI/RendererGUIRectangleGL.hpp>
#include <OpenGL/Renderer/GUI/RendererGUIScalableRectangleGL.hpp>

#include <algorithm>

using namespace ax;

RendererGUILayoutHandle RendererGL::createGUILayout()
{
    //Id id = m_content.layouts.add(std::make_unique<RendererGUILayoutGL>());
    //RendererGUILayoutGL* layout = m_content.layouts.get(id).get();
    //layout->id = id;

    return nullptr;
}
void RendererGL::destroyGUILayout(RendererGUILayoutHandle& layout)
{
    //RendererGUILayoutGL* layout = static_cast<RendererGUILayoutGL*>(layout);
    //m_content.layouts.remove(layout->id);
    layout = nullptr;
}

RendererGUILayoutGL::RendererGUILayoutGL(
    GLuint guiRectangleShader,
    GLuint guiScalableRectangleShader
) : 
m_guiRectangleShader(guiRectangleShader),
m_guiScalableRectangleShader(guiScalableRectangleShader)
{

}

RendererGUIRectangleHandle RendererGUILayoutGL::createRectangle()
{
    m_components.emplace_back(std::make_pair(
        0, std::make_unique<RendererGUIRectangleGL>(*this, m_guiRectangleShader)
    ));
    return static_cast<RendererGUIRectangleGL*>(m_components.back().second.get());
}
void RendererGUILayoutGL::destroyRectangle(RendererGUIRectangleHandle& handle)
{
    m_components.erase(std::remove_if(m_components.begin(), m_components.end(), 
        [&](std::pair<unsigned, std::unique_ptr<RendererGUIComponentGL>>& ptr)
            {return (ptr.second.get() == static_cast<RendererGUIRectangleGL*>(handle));}));
    handle = nullptr;
}

RendererGUIScalableRectangleHandle RendererGUILayoutGL::createScalableRectangle()
{
    //scalableRectangles.emplace_back(std::make_unique<RendererGUIScalableRectangleGL>());
    //return scalableRectangles.back().get();

    return nullptr;
}
void RendererGUILayoutGL::destroyScalableRectangle(RendererGUIScalableRectangleHandle& handle)
{
    /*scalableRectangles.erase(std::remove_if(scalableRectangles.begin(), scalableRectangles.end(), 
        [&](std::unique_ptr<RendererGUIScalableRectangleGL> ptr){ptr.get() == handle;}));
    handle = nullptr;*/
}

void RendererGUILayoutGL::draw() noexcept
{
    for(auto& component : m_components)
        component.second->draw();
}