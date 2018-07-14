#pragma once

#include <Config.hpp>

#if defined(AXION_GL_EXPORT)
	#define AXION_GL_API AXION_EXPORT
#else
	#define AXION_GL_API AXION_IMPORT
#endif