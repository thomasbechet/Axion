#include <Core/GUI/GUILayout.hpp>

#include <Core/Context/Engine.hpp>
#include <Core/GUI/GUI.hpp>

#include <algorithm>

using namespace ax;

GUILayout::GUILayout()
{
    m_handle = Engine::gui().createLayout();
}
GUILayout::~GUILayout()
{
    Engine::gui().destroyLayout(m_handle);
}

GUIButton& GUILayout::addButton() noexcept
{
    m_buttons.emplace_back(std::make_unique<GUIButton>(*this));
    return *m_buttons.back().get();
}
void GUILayout::removeButton(GUIButton& button) noexcept
{
    m_buttons.erase(std::remove_if(m_buttons.begin(), m_buttons.end(), 
        [&](auto& o){return (o.get() == &button);}), m_buttons.end());
}
GUIText& GUILayout::addText() noexcept
{
    m_texts.emplace_back(std::make_unique<GUIText>(*this));
    return *m_texts.back().get();
}
void GUILayout::removeText(GUIText& text) noexcept
{
    m_texts.erase(std::remove_if(m_texts.begin(), m_texts.end(), 
    [&](auto& o){return (o.get() == &text);}), m_texts.end());
}