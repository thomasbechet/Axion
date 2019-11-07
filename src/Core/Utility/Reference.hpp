#pragma once

#include <Core/Export.hpp>
#include <Core/Utility/ReferenceTracker.hpp>

#include <optional>

namespace ax
{
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

    private:
        std::optional<std::reference_wrapper<BasicReferenceTracker>> m_tracker;
    };

    /*template<typename T>
    class AXION_CORE_API Reference : public BasicReferenceTracker
    {
    public:
        T* get() noexcept;
        T* operator->() const noexcept;

    private:
        std::optional<std::reference_wrapper<T>> m_object;
    };*/
}