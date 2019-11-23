#pragma once

#include <vector>

namespace ax
{
    template<typename... Args>
    constexpr auto requirementsBuilder() noexcept
    {
        return std::vector<std::string>{Args::identifier...};
    } 
}

#define ENGINE_INIT(GAMEMODE) \
    int main(int argc, char* argv[]) \
    { \
        ax::Engine::initialize(); \
        ax::Engine::scene().gamemode.set<GAMEMODE>(); \
        ax::Engine::context().run(); \
        ax::Engine::terminate(); \
        std::cout << "end reached" << std::endl; \
        return 0;\
    } \

#define COMPONENT_IDENTIFIER(IDENTIFIER) \
    static inline const std::string identifier = IDENTIFIER; \

#define COMPONENT_REQUIREMENTS(...) \
    static inline const auto requirements = ax::requirementsBuilder<__VA_ARGS__>(); \

#define ASSET_IDENTIFIER(IDENTIFIER) \
    static inline const std::string identifier = IDENTIFIER; \

#define SYSTEM_IDENTIFIER(IDENTIFIER) \
    static inline const std::string identifier = IDENTIFIER; \

#define GAMEMODE_IDENTIFIER(IDENTIFIER) \
    static inline const std::string identifier = IDENTIFIER; \

