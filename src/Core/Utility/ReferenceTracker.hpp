#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/Reference.hpp>

namespace ax
{
    class AXION_CORE_API BasicReferenceTracker
    {
    public:
        virtual ~BasicReferenceTracker();

    public:
        BasicReference reference() noexcept;

        void increment() noexcept;
        void decrement() noexcept;
        unsigned count() const noexcept;

    private:
        unsigned m_referenceCount = 0;
    };

    /*template<typename T>
    class AXION_CORE_API ReferenceTracker : public IReferenceTracker
    {
    public:
        ReferenceTracker(T& object);

    private:
        std::reference_wrapper<T> m_object;
    };*/
}