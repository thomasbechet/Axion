#pragma once

namespace ax
{	
	//////////////////////
	//STATIC CONSTANTS
	//////////////////////
	constexpr double PI = 3.14159265359;
	
	template<typename T>
	static T radians(const T& degrees) noexcept
	{
		return (degrees * PI) / (T)180;
	}
	template<typename T>
	static void toRadians(const T& degrees) noexcept
	{
		degrees = (degrees * PI) / (T)180;
	}
	template<typename T>
	static T degrees(const T& radians) noexcept
	{
		return (radians * (T)180) / PI;
	}
	template<typename T>
	static void toDegrees(const T& radians) noexcept
	{
		radians = (radians * (T)180) / PI;
	}
}