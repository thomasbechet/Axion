#include <OpenGL/Renderer/GUI/RendererGUILayoutGL.hpp>
#include <OpenGL/Renderer/RendererGL.hpp>

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

RendererGUIRectangleHandle RendererGUILayoutGL::createRectangle()
{
    //rectangles.emplace_back(std::make_unique<RendererGUIRectangleGL>());
    //return rectangles.back().get();
    return nullptr;
}
void RendererGUILayoutGL::destroyRectangle(RendererGUIRectangleHandle& handle)
{
    /*rectangles.erase(std::remove_if(rectangles.begin(), rectangles.end(), 
        [&](std::unique_ptr<RendererGUIRectangleGL> ptr){ptr.get() == handle;}));
    handle = nullptr;*/
}

RendererGUIScalableRectangleHandle RendererGUILayoutGL::createScalableRectangle()
{
    //scalableRectangles.emplace_back(std::make_unique<RendererGUIScalableRectangleGL>());
    //return scalableRectangles.back().get();
}
void RendererGUILayoutGL::destroyScalableRectangle(RendererGUIScalableRectangleHandle& handle)
{
    /*scalableRectangles.erase(std::remove_if(scalableRectangles.begin(), scalableRectangles.end(), 
        [&](std::unique_ptr<RendererGUIScalableRectangleGL> ptr){ptr.get() == handle;}));
    handle = nullptr;*/
}

void RendererGUILayoutGL::draw() noexcept
{
    for(auto& component : components)
    {
        component.second->draw();
    }
}