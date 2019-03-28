#pragma once

#include <Core/Export.hpp>

class AXION_CORE_API NonCopyable
{
public:
    NonCopyable() = default;
    NonCopyable(const NonCopyable& other) = delete;
    NonCopyable& operator=(const NonCopyable& other) = delete;
};