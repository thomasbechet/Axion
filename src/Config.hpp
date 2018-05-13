#pragma once

/////////////////////////////
//AXION VERSION
/////////////////////////////
#define AXION_VERSION_MAJOR 0
#define AXION_VERSION_MINOR 0
#define AXION_VERSION_PATCH 0

/////////////////////////////
//IMPORT EXPORT
/////////////////////////////
#if defined(_MSV_VER)
    #define AXION_EXPORT __declspec(dllexport)
    #define AXION_IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
    #define AXION_EXPORT __attribute__((visibility("default")))
    #define AXION_IMPORT
#else
    #define AXION_EXPORT
    #define AXION_IMPORT
    #pragma warning Unknown linkage directive import/export semantics.
#endif

/////////////////////////////
//PLATFORM SUPPORT
/////////////////////////////
#if defined (_WIN32)
    #define AXION_PLATFORM_WINDOWS
#elif defined(__APPLE__)
    #define AXION_PLATFORM_APPLE
#elif defined(__linux__) || defined(__unix__)
    #define AXION_PLATFORM_UNIX
#endif