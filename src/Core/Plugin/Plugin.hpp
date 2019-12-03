#pragma once

#include <Core/Export.hpp>
#include <Core/Engine/Module.hpp>
#include <Core/Utility/LibraryLoader.hpp>

#include <map>

namespace ax
{
    class AXION_CORE_API Plugin : public Module
    {
    public:
        void initialize() noexcept override;
        void terminate() noexcept override;

    private:
        std::map<std::string, Utility::LibraryLoader> m_libraryHolder;
    };
}