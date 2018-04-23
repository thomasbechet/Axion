#pragma once

///////////////////////////////////
//Headers
///////////////////////////////////
#include <Core/Export.hpp>

#include <iostream>
#include <cmath>

namespace ax
{
	///////////////////////////////////
	//Vectors
	///////////////////////////////////
	template<typename T>
	class AXION_CORE_API Vector2
	{
	public:
		inline Vector2<T>(){}
		inline Vector2<T>(T x, T y)
		{
			this->x = x;
			this->y = y;
		}
		
		//////////////////////////
		//OPERATORS
		//////////////////////////
		inline Vector2<T> operator+(const Vector2<T>& vec){return Vector2<T>(x + vec.x, y + vec.y);}
		inline Vector2<T> operator-(const Vector2<T>& vec){return Vector2<T>(x - vec.x, y - vec.y);}
		inline Vector2<T> operator*(const Vector2<T>& vec){return Vector2<T>(x * vec.x, y * vec.y);}
		inline Vector2<T> operator*(const T& factor){return Vector2<T>(x * factor, y * factor);}
		inline Vector2<T> operator/(const Vector2<T>& vec){return Vector2<T>(x / vec.x, y / vec.y);}
		
		//////////////////////////
		//ALGEBRA
		//////////////////////////
		inline static T length(const Vector2<T>& vec)
		{
			return std::sqrt(vec.x * vec.x + vec.y * vec.y);
		}
		inline T length() const
		{
			return Vector2<T>::length(*this);
		}
		inline static Vector2<T> normalize(const Vector2<T>& vec)
		{
			T l = Vector2<T>::length(vec);
			return Vector2<T>(vec.x / l, vec.y / l);
		}
		inline void normalize()
		{
			*this = Vector2<T>::normalize(*this);
		}
		inline static T dot(const Vector2<T>& vec1, const Vector2<T>& vec2)
		{
			return (vec1.x * vec2.x + vec1.y * vec2.y);
		}
		inline T dot(const Vector2<T>& vec) const
		{
			return (x * vec.x + y * vec.y);
		}
		
		////////////////////
		//UTILITY
		////////////////////
		inline friend std::ostream& operator<<(std::ostream& out, const Vector2<T>& vec)
		{
			out << "[X=" << vec.x << " Y=" << vec.y << "]";
			return out;
		}
		
	public:
		T x = 0;
		T y = 0;
	};

	typedef Vector2<float> Vector2f;
	typedef Vector2<uint> Vector2u;
	typedef Vector2<int> Vector2i;
	typedef Vector2<double> Vector2d;

	template<typename T>
	class AXION_CORE_API Vector3
	{
	public:
		inline Vector3<T>(){}
		inline Vector3<T>(T x, T y, T z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}
		inline Vector3<T>(const Vector2<T> vec, T z)
		{
			this->x = vec.x;
			this->y = vec.y;
			this->z = z;
		}
		
		////////////////////
		//OPERATORS
		////////////////////
		inline Vector3<T> operator+(const Vector3<T> vec){return Vector3<T>(x + vec.x, y + vec.y, z + vec.z);}
		inline Vector3<T> operator-(const Vector3<T> vec){return Vector3<T>(x - vec.x, y - vec.y, z - vec.z);}
		inline Vector3<T> operator*(const Vector3<T> vec){return Vector3<T>(x * vec.x, y * vec.y, z * vec.z);}
		inline Vector3<T> operator*(const T& factor){return Vector3<T>(x * factor, y * factor, z * factor);}
		inline Vector3<T> operator/(const Vector3<T> vec){return Vector3<T>(x / vec.x, y / vec.y, z / vec.z);}
		
		//////////////////////////
		//ALGEBRA
		//////////////////////////
		inline static T length(const Vector3<T>& vec)
		{
			return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
		}
		inline T length() const
		{
			return Vector3<T>::length(*this);
		}
		inline static Vector3<T> normalize(const Vector3<T>& vec)
		{
			T l = Vector3<T>::length(vec);
			return Vector3<T>(vec.x / l, vec.y / l, vec.z / l);
		}
		inline void normalize()
		{
			*this = Vector3<T>::normalize(*this);
		}
		inline static T dot(const Vector3<T>& vec1, const Vector3<T>& vec2)
		{
			return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
		}
		inline T dot(const Vector3<T>& vec) const
		{
			return (x * vec.x + y * vec.y + z * vec.z);
		}
		inline static Vector3<T> cross(const Vector3<T>& vec1, const Vector3<T>& vec2)
		{
			return Vector3<T>(vec1.y * vec2.z - vec1.z * vec2.y, 
								vec1.z * vec2.x - vec1.x * vec2.z, 
								vec1.x * vec2.y - vec1.y * vec2.x);
		}
		inline Vector3<T> cross(const Vector3<T>& vec) const
		{
			return Vector3<T>(y * vec.z - z * vec.y,
								z * vec.x - x * vec.z,
								x * vec.y - y * vec.x);
		}
		
		////////////////////
		//UTILITY
		////////////////////
		inline friend std::ostream& operator<<(std::ostream& out, const Vector3<T>& vec)
		{
			out << "[X=" << vec.x << " Y=" << vec.y << " Z=" << vec.z << "]";
			return out;
		}
		
	public:
		T x = 0;
		T y = 0;
		T z = 0;
	};

	typedef Vector3<float> Vector3f;
	typedef Vector3<uint> Vector3u;
	typedef Vector3<int> Vector3i;
	typedef Vector3<double> Vector3d;

	template<typename T>
	class AXION_CORE_API Vector4
	{
	public:
		inline Vector4<T>(){}
		inline Vector4<T>(T x, T y, T z, T w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}
		inline Vector4<T>(const Vector3<T> vec, T w)
		{
			this->x = vec.x;
			this->y = vec.y;
			this->z = vec.z;
			this->w = w;
		}
		inline Vector4<T>(const Vector2<T> vec, T z, T w)
		{
			this->x = vec.x;
			this->y = vec.y;
			this->z = z;
			this->w = w;
		}
		
		///////////////////////
		//OPERATORS
		///////////////////////
		inline Vector4<T> operator+(const Vector4<T> vec){return Vector4<T>(x + vec.x, y + vec.y, z + vec.z, w + vec.w);}
		inline Vector4<T> operator-(const Vector4<T> vec){return Vector4<T>(x - vec.x, y - vec.y, z - vec.z, w - vec.w);}
		inline Vector4<T> operator*(const Vector4<T> vec){return Vector4<T>(x * vec.x, y * vec.y, z * vec.z, w * vec.w);}
		inline Vector4<T> operator*(const T& factor){return Vector4<T>(x * factor, y * factor, z * factor, w * factor);}
		inline Vector4<T> operator/(const Vector4<T> vec){return Vector4<T>(x / vec.x, y / vec.y, z / vec.z, w / vec.w);}
		
		//////////////////////////
		//ALGEBRA
		//////////////////////////
		inline static T length(const Vector4<T>& vec)
		{
			return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
		}
		inline T length() const
		{
			return Vector4<T>::length(*this);
		}
		inline static Vector4<T> normalize(const Vector4<T>& vec)
		{
			T l = Vector4<T>::length(vec);
			return Vector4<T>(vec.x / l, vec.y / l, vec.z / l, vec.w / l);
		}
		inline void normalize()
		{
			*this = Vector4<T>::normalize(*this);
		}
		inline static T dot(const Vector4<T>& vec1, const Vector4<T>& vec2)
		{
			return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z + vec1.w * vec2.w);
		}
		inline T dot(const Vector4<T>& vec)
		{
			return (x * vec.x + y * vec.y + z * vec.z + w * vec.w);
		}
		
		////////////////////
		//UTILITY
		////////////////////
		inline friend std::ostream& operator<<(std::ostream& out, const Vector4<T>& vec)
		{
			out << "[X=" << vec.x << " Y=" << vec.y << " Z=" << vec.z << " W=" << vec.w << "]";
			return out;
		}
		
	public:
		T x = 0;
		T y = 0;
		T z = 0;
		T w = 0;
	};

	typedef Vector4<float> Vector4f;
	typedef Vector4<uint> Vector4u;
	typedef Vector4<int> Vector4i;
	typedef Vector4<double> Vector4d;
}


