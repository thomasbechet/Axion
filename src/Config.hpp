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