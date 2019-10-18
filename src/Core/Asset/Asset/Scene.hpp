#pragma once

#include <Core/Export.hpp>
#include <Core/Asset/Asset.hpp>
#include <Core/Utility/Path.hpp>

#include <string>

namespace ax
{
    class AXION_CORE_API Scene : public Asset
    {
    public:
        struct Parameters
        {
            Path source;
            std::string json;
        };

    public:
        static const std::string type;

        Scene(std::string name, const Parameters& parameters);

    private:
        bool onLoad() noexcept override;
        bool onValidate() noexcept override;
        bool onUnload() noexcept override;
        void onError() noexcept override;

    private:
        Parameters m_parameters;

        std::string m_error;
    };
}