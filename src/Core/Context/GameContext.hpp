#pragma onace

///////////////////
//HEADERS
///////////////////
#include <Core/Export.hpp>
#include <Core/Utility/ConfigParser.hpp>

namespace ax
{
    class AXION_CORE_API GameContext
    {
    public:
        ConfigParser& config() noexcept;

    private:
        ConfigParser m_configParser;
    };
}