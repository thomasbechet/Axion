#pragma once

////////////////
//HEADERS
////////////////
#include <Core/Export.hpp>
#include <Core/Utility/Time.hpp>

#include <vector>

namespace ax
{
    class AXION_CORE_API TimeRecorder
    {
    public:
        TimeRecorder();
        TimeRecorder(unsigned size);

        Time getAverage() const noexcept;
        void record(Time& time) noexcept;
        void setRecordSize(unsigned size) noexcept;
        unsigned getRecordSize() const noexcept;

    private:
        unsigned m_current = 0;
        std::vector<Time> m_times;
    };
}