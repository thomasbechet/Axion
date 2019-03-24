#include <Core/GUI/Widget/GUIText.hpp>

using namespace ax;

GUIText::GUIText(GUILayout& layout)
{
    m_handle = Engine::gui().createButton(*this);
}
GUIText::~GUIText()
{
    Engine::gui().destroyButton(m_handle);
}