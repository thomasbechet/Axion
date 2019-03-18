#include <Core/GUI/Widget/GUIButton.hpp>

using namespace ax;

GUIButton::GUIButton(GUILayout& layout) : GUIRectangle(layout)
{
    m_handle = Engine::gui().createButton(*this);
}
GUIButton::~GUIButton()
{
    Engine::gui().destroyButton(m_handle);
}