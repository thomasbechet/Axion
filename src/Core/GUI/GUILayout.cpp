#include <Core/GUI/GUILayout.hpp>

using namespace ax;

GUILayout::GUILayout()
{
    m_handle = Engine::gui().createLayout();
}
GUILayout::~GUILayout()
{
    Engine::gui().destroyLayout(m_handle);
}