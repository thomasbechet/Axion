#pragma once

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
		Quaternion(){}
		Quaternion(T _x, T _y, T _z, T _w)
		{
			x = _x;
			y = _y;
			z = _z;
			w = _w;
		}
		Quaternion(const T& angle, const Vector3<T>& axis)
		{
			w = std::cos(angle / (T)2);
			x = axis.x * std::sin(angle / (T)2);
			y = axis.y * std::sin(angle / (T)2);
			z = axis.z * std::sin(angle / (T)2);
		}
		
		///////////////////////
		//OPERATORS
		///////////////////////
		Vector3<T> operator*(const Vector3<T>& v)
		{
			Vector3<T> u(x, y, z);
			return 2 * Vector3<T>::dot(u, v) * u + (w * w - Vector3<T>::dot(u, u)) * v + 2 * w * Vector3<T>::cross(u, v);
		}
		Quaternion<T> operator*(const Quaternion<T>& q)
		{
			return Quaternion<T>(
				w * q.w - x * q.x - y * q.y - z * q.z,
				w * q.x + x * q.w + y * q.z - z * q.y,
				w * q.y + y * q.w + z * q.x - x * q.z,
				w * q.z + z * q.w + x * q.y - y * q.x
			);
		}
		Quaternion<T>& operator*=(const Quaternion<T>& q)
		{
			T w_val = w * q.w - x * q.x - y * q.y - z * q.z;
			T x_val = w * q.x + x * q.w + y * q.z - z * q.y; 
			T y_val = w * q.y + y * q.w + z * q.x - x * q.z;
			T z_val = w * q.z + z * q.w + x * q.y - y * q.x; 
			
			w = w_val;
			x = x_val;
			y = y_val;
			z = z_val;

			return (*this);
		}
		
		////////////////////
		//ALGEBRA
		////////////////////
		static Matrix4<T> toMatrix(Quaternion<T> quat) noexcept
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
		static Quaternion<T> lerp(const Quaternion<T>& a, const Quaternion<T>& b, const float t) noexcept
		{
			Quaternion r;
			float t1 = 1 - t;
			r.x = t1 * a.x + t * b.x;
			r.y = t1 * a.y + t * b.y;
			r.z = t1 * a.z + t * b.z;
			r.w = t1 * a.w + t * b.w;
			r.normalize();

			return r;
		}
		static Quaternion<T> slerp(const Quaternion<T>& a, const Quaternion<T>& b, const float t) noexcept
		{
			Quaternion r;
			float t1 = 1 - t;
			float Wa, Wb;
			float theta = acos(a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
			float sn = sin(theta);
			Wa = sin(t1 * theta) / sn;
			Wb = sin(t * theta) / sn;
			r.x = Wa * a.x + Wb * b.x;
			r.y = Wa * a.y + Wb * b.y;
			r.z = Wa * a.z + Wb * b.z;
			r.w = Wa * a.w + Wb * b.w;
			r.normalize();

			return r;
		}
		
	public:
		T x = (T)0;
		T y = (T)0; 
		T z = (T)0;
		T w = (T)1;
	};
	
	using Quaternionf = Quaternion<float>;
	using Quaterniond = Quaternion<double>;
}

