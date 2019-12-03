#pragma once

#include <Core/Export.hpp>
#include <Core/Scene/System/System.hpp>

#include <vector>
#include <memory>

namespace ax
{
    class AXION_CORE_API SystemManager : public NonCopyable
    {
    public:
        ~SystemManager();

    public:
        void start() noexcept;
        void stop() noexcept;
        void update() noexcept;
        void fixedUpdate() noexcept;

    private:
        template<typename S>
        size_t generateLocation() noexcept;
        template<typename S>
        size_t getLocation() noexcept;

    public:
        void logInfo() const noexcept;

        template<typename S, typename... Args>
        S& add(Args&&... args) noexcept;
        template<typename S>
        void remove() noexcept;

        void removeAll() noexcept;

        template<typename S>
        bool exists() noexcept;
        template<typename S>
        S& get() noexcept;

        //SEQUENCES/////////////////
        template<typename S1, typename S2>
        void sequenceSwap() noexcept;
        template<typename S1, typename S2>
        void sequenceBefore() noexcept;
        template<typename S1, typename S2>
        void sequenceAfter() noexcept;
        template<typename S>
        void sequenceTop() noexcept;
        template<typename S>
        void sequenceBottom() noexcept;
        template<typename S>
        void sequenceMoveUp() noexcept;
        template<typename S>
        void sequenceMoveDown() noexcept;

    private:
        std::vector<std::pair<bool, std::unique_ptr<System>>> m_systems;
        std::vector<std::string> m_names;
        std::vector<size_t> m_sequence;
    };
}