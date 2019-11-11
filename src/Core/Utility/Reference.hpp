#pragma once

#include <Core/Export.hpp>

namespace ax
{
    class BasicReferenceTracker;
    template<typename T>
    class ReferenceTracker;

    class AXION_CORE_API BasicReference
    {
    public:
        BasicReference() = default;
        BasicReference(BasicReferenceTracker& tracker);
        BasicReference(const BasicReference& reference);
        virtual ~BasicReference();

        BasicReference& operator=(const BasicReference& other);
        
        explicit operator bool() const noexcept;
        void reset() noexcept;
        bool isValid() const noexcept;

    protected:
        BasicReferenceTracker* m_tracker = nullptr;
    };

    template<typename T>
    class AXION_CORE_API Reference : public BasicReference
    {
    public:
        Reference() = default;
        Reference(ReferenceTracker<T>& tracker);
        Reference(const Reference<T>& reference);
        ~Reference();

        Reference<T>& operator=(const Reference<T>& other);
        Reference<T>& operator=(ReferenceTracker<T>& tracker);

        T* get() const noexcept;
        T* operator->() const noexcept;

    private:
        T* m_object = nullptr;
    };

    class AXION_CORE_API BasicReferenceTracker
    {
    public:
        virtual ~BasicReferenceTracker();

    public:
        BasicReference basicReference() noexcept;

        void increment() noexcept;
        void decrement() noexcept;
        unsigned count() const noexcept;

    private:
        unsigned m_referenceCount = 0;
    };

    template<typename T>
    class AXION_CORE_API ReferenceTracker : public BasicReferenceTracker
    {
    public:
        ReferenceTracker(T& object);

        Reference<T> reference() noexcept;

        T* get() const noexcept;
        T* operator->() const noexcept;

    private:
        T* m_object = nullptr;
    };
}