#include <Core/Utility/Reference.hpp>

#include <Core/Context/Engine.hpp>

using namespace ax;

BasicReference::BasicReference(BasicReferenceTracker& tracker)
{   
    m_tracker = &tracker;
    m_tracker->increment();
}
BasicReference::BasicReference(const BasicReference& reference)
{
    operator=(reference);
}
BasicReference::~BasicReference()
{
    reset();
}

BasicReference& BasicReference::operator=(const BasicReference& other)
{
    reset();
    if(other)
    {
        m_tracker = other.m_tracker;
        m_tracker->increment();
    }
    return *this;
}

BasicReference::operator bool() const noexcept
{
    return isValid();
}
void BasicReference::reset() noexcept
{
    if(m_tracker)
        m_tracker->decrement();
    
    m_tracker = nullptr;
}
bool BasicReference::isValid() const noexcept
{
    return (m_tracker != nullptr);
}

BasicReferenceTracker::~BasicReferenceTracker()
{
    if(m_referenceCount > 0)
        Engine::interrupt("Trying to destroy references tracker with remaining references (" + std::to_string(m_referenceCount) + ")");
}

BasicReference BasicReferenceTracker::basicReference() noexcept
{
    return BasicReference(*this);
}

void BasicReferenceTracker::increment() noexcept
{
    m_referenceCount++;
}
void BasicReferenceTracker::decrement() noexcept
{
    if(m_referenceCount <= 0)
        Engine::interrupt("Count not decrement references tracker because it has no reference");

    m_referenceCount--;
}
unsigned BasicReferenceTracker::count() const noexcept
{
    return m_referenceCount;
}