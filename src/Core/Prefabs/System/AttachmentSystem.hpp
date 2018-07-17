#pragma once

/////////////
//HEADERS
/////////////
#include <Core/Export.hpp>
#include <Core/System/System.hpp>

namespace ax
{
    class AXION_CORE_API AttachmentSystem : public System
    {
    public:
        static std::string name() noexcept;

        void onInitialize() override;
        void onUpdate() override;
        void onTerminate() override;
    };
}