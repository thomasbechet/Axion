#include <Core/GUI/Widget/GUIWidget.hpp>

using namespace ax;

GUIWidget::GUIWidget(GUILayout& layout) : m_layout(layout)
{
    
}

void GUIWidget::setPosition(int x, int y) noexcept
{
    setTranslation(Vector2i(x, y));
}
void GUIWidget::setPosition(Vector2i position) noexcept
{
    m_transform.setTranslation(position);
}
Vector2i GUIWidget::getPosition() const noexcept
{
    return m_transform.getTranslation();
}
void GUIWidget::setRotation(float rotation) noexcept
{
    m_transform.setRotation(rotation);
}
float GUIWidget::getRotation() const noexcept
{
    return m_transform.getRotation();
}
void GUIWidget::setScale(float x, float y) noexcept
{
    m_transform.setScale(x, y);
}
void GUIWidget::setScale(Vector2f scale) noexcept
{
    m_transform.setScale(scale);
}
Vector2f GUIWidget::getScale() const noexcept
{
    return m_transform.getScale();
}

void GUIWidget::attachTo(GUIWidget& component) noexcept
{
    m_parent = component;
    m_transform.attachTo(component.m_transform);
}
void GUIWidget::detach() noexcept
{
    m_parent = nullptr;
    m_transform.detach();
}   

bool GUIWidget::isAttached() const noexcept
{
    return m_parent != nullptr;
}
GUIWidget& GUIWidget::getParent() const noexcept
{
    return *m_parent;
}
bool GUIWidget::hasChild() const noexcept
{
    return m_firstChild != nullptr;
}
GUIWidget& GUIWidget::getFirstChild() const noexcept
{
    return *m_firstChild;
}
bool GUIWidget::hasSibling() const noexcept
{
    return m_nextSibling != nullptr;
}
GUIWidget& GUIWidget::getNextSibling() const noexcept
{
    return *m_nextSibling;
}