#pragma once

///////////////////////////////////
//Headers
///////////////////////////////////
#include <Core/Export.hpp>

namespace ax
{	
	//////////////////////
	//STATIC CONSTANTS
	//////////////////////
	const double PI = 3.14159265359;
	
	template<typename T>
	inline static T radians(const T& degrees)
	{
		return (degrees * PI) / (T)180;
	}
	template<typename T>
	inline static void toRadians(const T& degrees)
	{
		degrees = (degrees * PI) / (T)180;
	}
	template<typename T>
	inline static T degrees(const T& radians)
	{
		return (radians * (T)180) / PI;
	}
	template<typename T>
	inline static void toDegrees(const T& radians)
	{
		radians = (radians * (T)180) / PI;
	}
}