#pragma once

#include <Config.hpp>

#if defined(AXION_CORE_EXPORT)
	#define AXION_CORE_API AXION_EXPORT
#else
	#define AXION_CORE_API AXION_IMPORT
#endif