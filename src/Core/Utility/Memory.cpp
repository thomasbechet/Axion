#include <Core/Utility/Memory.hpp>

using namespace ax;

Memory::Memory(){}
Memory::Memory(unsigned long memory) : m_memory(memory){}

unsigned long Memory::asBytes() const noexcept
{
    return m_memory;
}
float Memory::asKilobytes() const noexcept
{
    return (float)m_memory / 1000.0f;
}
float Memory::asMegabytes() const noexcept
{
    return (float)m_memory / 1000000.0f;
}
double Memory::asGigabytes() const noexcept
{
    return (double)m_memory / 1000000000.0f;
}

Memory Memory::operator+(const Memory& m)
{
    return Memory(m_memory + m.m_memory);
}
Memory Memory::operator-(const Memory& m)
{
    return Memory(m_memory - m.m_memory);
}
Memory Memory::operator+=(const Memory& m)
{
    return Memory(m_memory += m.m_memory);
}
Memory Memory::operator-=(const Memory& m)
{
    return Memory(m_memory -= m.m_memory);
}
Memory Memory::operator*(const Memory& m)
{
    return Memory(m_memory * m.m_memory);
}
Memory Memory::operator*(const unsigned long& k)
{
    return Memory(m_memory * k);
}
Memory Memory::operator/(const Memory& m)
{
    return Memory(m_memory / m.m_memory);
}
Memory Memory::operator/(const unsigned long& k)
{
    return Memory(m_memory / k);
}