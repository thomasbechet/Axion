#pragma once

#include <core/export.hpp>

#include <string>

namespace ax
{
    class AXION_CORE_API json_attributes
    {
    public:
        static inline const std::string source = "source";
        static inline const std::string type = "type";
        static inline const std::string name = "name";
        static inline const std::string assets = "assets";
        static inline const std::string vertex = "vertex";
        static inline const std::string fragment = "fragment";
    };
}