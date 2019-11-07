#include <Core/Utility/ReferenceTracker.hpp>

#include <exception>

using namespace ax;

BasicReferenceTracker::~BasicReferenceTracker()
{
    if(m_referenceCount > 0)
        throw std::runtime_error("Could not destroy tracker with there are remaining references");
}

BasicReference BasicReferenceTracker::reference() noexcept
{
    return BasicReference(*this);
}

void BasicReferenceTracker::increment()
{
    m_referenceCount++;
}
void BasicReferenceTracker::decrement()
{
    if(m_referenceCount <= 0)
        throw std::runtime_error("Count not decrement reference tracker because it has no reference");

    m_referenceCount--;
}
unsigned BasicReferenceTracker::count() const noexcept
{
    return m_referenceCount;
}