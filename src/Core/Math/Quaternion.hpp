#pragma once

/////////////////////////
//Headers
/////////////////////////
#include <Core/Export.hpp>
#include <Core/Math/Vector.hpp>
#include <Core/Math/Matrix.hpp>

#include <cmath>

namespace ax
{
	/////////////////////////
	//QUATERNION
	/////////////////////////
	template<typename T>
	class AXION_CORE_API Quaternion
	{
	public:
		inline Quaternion()
		{
			
		}
		inline Quaternion(const T& angle, const Vector3<T>& axis)
		{
			w = std::cos(angle / (T)2);
			x = axis.x * std::sin(angle / (T)2);
			y = axis.y * std::sin(angle / (T)2);
			z = axis.z * std::sin(angle / (T)2);
		}
		
		///////////////////////
		//OPERATORS
		///////////////////////
		
		///////////////////////
		//ALGEBRA
		///////////////////////
		inline static Matrix4<T> toMatrix(Quaternion quat)
		{
			const T n = (T)1 / std::sqrt(quat.x * quat.x + quat.y * quat.y + quat.z * quat.z + quat.w * quat.w);
			quat.x *= n;
			quat.y *= n;
			quat.z *= n;
			quat.w *= n;
			
			return Matrix4<T>(
				(T)1 - (T)2 * quat.y * quat.y - (T)2 * quat.z * quat.z,
				(T)2 * quat.x * quat.y - (T)2 * quat.z * quat.w,
				(T)2 * quat.x * quat.z + (T)2 * quat.y * quat.w,
				(T)0,
				
				(T)2 * quat.x * quat.y + (T)2 * quat.z * quat.w,
				(T)1 - (T)2 * quat.x * quat.x - (T)2 * quat.z * quat.z,
				(T)2 * quat.y * quat.z - (T)2 * quat.x * quat.w,
				(T)0,
				
				(T)2 * quat.x * quat.z - (T)2 * quat.y * quat.w,
				(T)2 * quat.y * quat.z + (T)2 * quat.x * quat.w,
				(T)1 - (T)2 * quat.x * quat.x - (T)2 * quat.y * quat.y,
				(T)0,
				
				(T)0,
				(T)0,
				(T)0,
				(T)1
			);
		}
		
	public:
		T w = (T)0;
		T x = (T)0;
		T y = (T)0; 
		T z = (T)0;
	};

	typedef Quaternion<float> Quaternionf;
	typedef Quaternion<double> Quaterniond;
	//typedef AQuaternion<float> AQuaternion;
}

