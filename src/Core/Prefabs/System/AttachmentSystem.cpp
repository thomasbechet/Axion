#include <Core/Prefabs/System/AttachmentSystem.hpp>

using namespace ax;

std::string AttachmentSystem::name() noexcept
{
    return "AttachmentSystem";
}

void AttachmentSystem::onInitialize()
{
    m_list = &Game::world().components().getList<AttachmentComponent>();
}
void AttachmentSystem::onUpdate()
{
    auto it = Game:
}
void AttachmentSystem::onTerminate()
{

}