#include <Core/Utility/TimeRecorder.hpp>

using namespace ax;

TimeRecorder::TimeRecorder()
{
    setRecordSize(1);
}
TimeRecorder::TimeRecorder(unsigned size)
{
    setRecordSize(size);
}

Time TimeRecorder::getAverage() const noexcept
{
    Time sum;
    for(auto it = m_times.begin(); it != m_times.end(); it++)
        sum += *it;

    return sum / m_times.size();
}
void TimeRecorder::record(Time& time) noexcept
{
    m_times[m_current] = time;
    m_current = (m_current + 1) % m_times.size();
}
void TimeRecorder::setRecordSize(unsigned size) noexcept
{
    m_times.clear();
    m_times.resize(size);
    m_current = 0;
}
unsigned TimeRecorder::getRecordSize() const noexcept
{
    return m_times.size();
}