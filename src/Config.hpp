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
#if !defined(AXION_STATIC)
	#define AXION_API_EXPORT __declspec(dllexport)
    #define AXION_API_IMPORT __declspec(dllimport)
#else
	//AXION_STATIC declared
	#define AXION_API_EXPORT
	#define AXION_API_IMPORT
#endif