#include <Core/Utility/Reference.hpp>

using namespace ax;

BasicReference::BasicReference(BasicReferenceTracker& tracker)
{   
    m_tracker = tracker;
    m_tracker.value().increment();
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
        m_tracker.value().increment();
    }
    return *this;
}

explicit BasicReference::operator bool() const noexcept
{
    return isValid();
}
void BasicReference::reset() noexcept
{
    if(m_tracker)
    {
        m_tracker.value().decrement();
        m_tracker.reset();
    } 
    
    m_tracker.reset()
}
bool BasicReference::isValid() const noexcept
{
    return m_tracker.has_value();
}