#pragma once

#include <Core/Export.hpp>

namespace ax
{
    class AXION_CORE_API Memory
    {
    public:
        Memory();
        Memory(unsigned long memory);

        unsigned long asBytes() const noexcept;
        float asKilobytes() const noexcept;
        float asMegabytes() const noexcept;
        double asGigabytes() const noexcept;

        Memory operator+(const Memory& m);
        Memory operator-(const Memory& m);
        Memory operator+=(const Memory& m);
        Memory operator-=(const Memory& m);
        Memory operator*(const Memory& m);
        Memory operator*(const unsigned long& k);
        Memory operator/(const Memory& m);
        Memory operator/(const unsigned long& k);

    private:
        unsigned long m_memory = 0;
    };
}