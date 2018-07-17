#pragma once

///////////////
//HEADERS
///////////////
#include <Core/Export.hpp>
#include <Core/World/Entity/Entity.hpp>
#include <Core/World/Entity/Component.hpp>

namespace ax
{
    class AXION_CORE_API AttachmentComponent : ax::Component
    {
    public:
        static std::string name(){return "Attachment";}
        void load(const Entity& entity) noexcept;
        void unload() noexcept;

        void attachTo(const Entity& entity) noexcept;
        void detach() noexcept;
        bool isAttached() const noexcept;
        Entity& getParent() const noexcept;

        Transform* transform = nullptr;
    
    private:
        ComponentList<AttachmentComponent>& m_list;
        ComponentIterator<AttachmentComponent> m_iterator;
    };
}