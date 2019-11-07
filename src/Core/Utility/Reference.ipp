#pragma once

#include <Core/Utility/Reference.hpp>

namespace ax
{
    template<typename T>
    Reference<T>::Reference(ReferenceTracker<T>& tracker)
    {
        operator=(tracker);
    }
    template<typename T>
    Reference<T>::Reference(const Reference<T>& reference)
    {
        operator=(reference);
    }
    template<typename T>
    Reference<T>::~Reference()
    {
        reset();
    }

    template<typename T>
    Reference<T>& Reference<T>::operator=(const Reference<T>& other)
    {
        reset();
        if(other)
        {
            m_tracker = other.m_tracker;
            m_tracker->increment();
            m_object = other.m_object;
        }
        return *this;
    }
    template<typename T>
    Reference<T>& Reference<T>::operator=(ReferenceTracker<T>& tracker)
    {
        m_tracker = static_cast<BasicReferenceTracker*>(&tracker);
        m_tracker->increment();
        m_object = tracker.get();
        return *this;
    }

    template<typename T>
    T* Reference<T>::get() const noexcept
    {
        return m_object;
    }
    template<typename T>
    T* Reference<T>::operator->() const noexcept
    {
        return m_object;
    }

    template<typename T>
    ReferenceTracker<T>::ReferenceTracker(T& object) : 
        BasicReferenceTracker(),
        m_object(&object)
    {

    }

    template<typename T>
    Reference<T> ReferenceTracker<T>::reference() noexcept
    {
        return Reference<T>(*this);
    }

    template<typename T>
    T* ReferenceTracker<T>::get() const noexcept
    {
        return m_object;
    }
    template<typename T>
    T* ReferenceTracker<T>::operator->() const noexcept
    {
        return m_object;
    }
}