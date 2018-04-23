#pragma once

#include <Config.hpp>

#if defined(AXION_API_EXPORT)
	#define AXION_CORE_API AXION_API_EXPORT
#else
	#define AXION_CORE_API AXION_API_IMPORT
#endif