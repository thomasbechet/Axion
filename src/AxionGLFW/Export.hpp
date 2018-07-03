#pragma once

#include <Config.hpp>

#if defined(AXION_GLFW_EXPORT)
	#define AXION_GLFW_API AXION_EXPORT
#else
	#define AXION_GLFW_API AXION_IMPORT
#endif