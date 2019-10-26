#pragma once

#define ENGINE_INIT(GAMEMODE) \
    int main(int argc, char* argv[]) \
    { \
        ax::Engine::initialize(); \
        ax::Engine::scene().gamemode.set<GAMEMODE>(); \
        ax::Engine::context().run(); \
        ax::Engine::terminate(); \
        return 0;\
    } \

