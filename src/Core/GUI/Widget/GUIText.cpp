#include <Core/GUI/Widget/GUILabel.hpp>

using namespace ax;

GUILabel::GUILabel(GUILayout& layout)
{
    m_handle = Engine::gui().createButton(*this);
}
GUILabel::~GUILabel()
{
    Engine::gui().destroyButton(m_handle);
}