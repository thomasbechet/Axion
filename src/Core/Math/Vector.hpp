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
		Vector2<T>(){}
		Vector2<T>(T x, T y)
		{
			this->x = x;
			this->y = y;
		}
		
		//////////////////////////
		//OPERATORS
		//////////////////////////
		Vector2<T> operator+(const Vector2<T>& vec){return Vector2<T>(x + vec.x, y + vec.y);}
		Vector2<T> operator-(const Vector2<T>& vec){return Vector2<T>(x - vec.x, y - vec.y);}
		Vector2<T> operator+=(const Vector2<T>& vec){return Vector2<T>(x += vec.x, y += vec.y);}
		Vector2<T> operator-=(const Vector2<T>& vec){return Vector2<T>(x -= vec.x, y -= vec.y);}
		Vector2<T> operator*(const Vector2<T>& vec){return Vector2<T>(x * vec.x, y * vec.y);}
		Vector2<T> operator*(const T& factor){return Vector2<T>(x * factor, y * factor);}
		Vector2<T> operator/(const Vector2<T>& vec){return Vector2<T>(x / vec.x, y / vec.y);}
		
		//////////////////////////
		//ALGEBRA
		//////////////////////////
		static T length(const Vector2<T>& vec) noexcept
		{
			return std::sqrt(vec.x * vec.x + vec.y * vec.y);
		}
		T length() const noexcept
		{
			return Vector2<T>::length(*this);
		}
		static Vector2<T> normalize(const Vector2<T>& vec) noexcept
		{
			T l = Vector2<T>::length(vec);
			return Vector2<T>(vec.x / l, vec.y / l);
		}
		void normalize() noexcept
		{
			*this = Vector2<T>::normalize(*this);
		}
		static T dot(const Vector2<T>& vec1, const Vector2<T>& vec2) noexcept
		{
			return (vec1.x * vec2.x + vec1.y * vec2.y);
		}
		T dot(const Vector2<T>& vec) const noexcept
		{
			return (x * vec.x + y * vec.y);
		}
		
		////////////////////
		//UTILITY
		////////////////////
		friend std::ostream& operator<<(std::ostream& out, const Vector2<T>& vec)
		{
			out << "[X=" << vec.x << " Y=" << vec.y << "]";
			return out;
		}
		
	public:
		T x = 0;
		T y = 0;
	};

	using Vector2f = Vector2<float>;
	using Vector2u = Vector2<unsigned>;
	using Vector2i = Vector2<int>;
	using Vector2d = Vector2<double>;

	template<typename T>
	class AXION_CORE_API Vector3
	{
	public:
		Vector3<T>(){}
		Vector3<T>(T x, T y, T z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}
		Vector3<T>(const Vector2<T> vec, T z)
		{
			this->x = vec.x;
			this->y = vec.y;
			this->z = z;
		}
		
		////////////////////
		//OPERATORS
		////////////////////
		Vector3<T> operator+(const Vector3<T> vec){return Vector3<T>(x + vec.x, y + vec.y, z + vec.z);}
		Vector3<T> operator-(const Vector3<T> vec){return Vector3<T>(x - vec.x, y - vec.y, z - vec.z);}
		Vector3<T> operator+=(const Vector3<T>& vec){return Vector3<T>(x += vec.x, y += vec.y, z += vec.z);}
		Vector3<T> operator-=(const Vector3<T>& vec){return Vector3<T>(x -= vec.x, y -= vec.y, z -= vec.z);}
		Vector3<T> operator*(const Vector3<T> vec){return Vector3<T>(x * vec.x, y * vec.y, z * vec.z);}
		Vector3<T> operator*(const T& factor){return Vector3<T>(x * factor, y * factor, z * factor);}
		Vector3<T> operator/(const Vector3<T> vec){return Vector3<T>(x / vec.x, y / vec.y, z / vec.z);}
		
		//////////////////////////
		//ALGEBRA
		//////////////////////////
		static T length(const Vector3<T>& vec) noexcept
		{
			return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
		}
		T length() const noexcept
		{
			return Vector3<T>::length(*this);
		}
		static Vector3<T> normalize(const Vector3<T>& vec) noexcept
		{
			T l = Vector3<T>::length(vec);
			return Vector3<T>(vec.x / l, vec.y / l, vec.z / l);
		}
		void normalize() noexcept
		{
			*this = Vector3<T>::normalize(*this);
		}
		static T dot(const Vector3<T>& vec1, const Vector3<T>& vec2) noexcept
		{
			return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
		}
		T dot(const Vector3<T>& vec) const noexcept
		{
			return (x * vec.x + y * vec.y + z * vec.z);
		}
		static Vector3<T> cross(const Vector3<T>& vec1, const Vector3<T>& vec2) noexcept
		{
			return Vector3<T>(vec1.y * vec2.z - vec1.z * vec2.y, 
								vec1.z * vec2.x - vec1.x * vec2.z, 
								vec1.x * vec2.y - vec1.y * vec2.x);
		}
		Vector3<T> cross(const Vector3<T>& vec) const noexcept
		{
			return Vector3<T>(y * vec.z - z * vec.y,
								z * vec.x - x * vec.z,
								x * vec.y - y * vec.x);
		}
		
		////////////////////
		//UTILITY
		////////////////////
		friend std::ostream& operator<<(std::ostream& out, const Vector3<T>& vec)
		{
			out << "[X=" << vec.x << " Y=" << vec.y << " Z=" << vec.z << "]";
			return out;
		}
		
	public:
		T x = 0;
		T y = 0;
		T z = 0;
	};

	using Vector3f = Vector3<float>;
	using Vector3u = Vector3<unsigned>;
	using Vector3i = Vector3<int>;
	using Vector3d = Vector3<double>;

	template<typename T>
	class AXION_CORE_API Vector4
	{
	public:
		Vector4<T>(){}
		Vector4<T>(T x, T y, T z, T w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}
		Vector4<T>(const Vector3<T> vec, T w)
		{
			this->x = vec.x;
			this->y = vec.y;
			this->z = vec.z;
			this->w = w;
		}
		Vector4<T>(const Vector2<T> vec, T z, T w)
		{
			this->x = vec.x;
			this->y = vec.y;
			this->z = z;
			this->w = w;
		}
		
		///////////////////////
		//OPERATORS
		///////////////////////
		Vector4<T> operator+(const Vector4<T> vec){return Vector4<T>(x + vec.x, y + vec.y, z + vec.z, w + vec.w);}
		Vector4<T> operator-(const Vector4<T> vec){return Vector4<T>(x - vec.x, y - vec.y, z - vec.z, w - vec.w);}
		Vector4<T> operator+=(const Vector4<T>& vec){return Vector4<T>(x += vec.x, y += vec.y, z += vec.z, w += vec.w);}
		Vector4<T> operator-=(const Vector4<T>& vec){return Vector4<T>(x -= vec.x, y -= vec.y, z -= vec.z, w -= vec.w);}
		Vector4<T> operator*(const Vector4<T> vec){return Vector4<T>(x * vec.x, y * vec.y, z * vec.z, w * vec.w);}
		Vector4<T> operator*(const T& factor){return Vector4<T>(x * factor, y * factor, z * factor, w * factor);}
		Vector4<T> operator/(const Vector4<T> vec){return Vector4<T>(x / vec.x, y / vec.y, z / vec.z, w / vec.w);}
		
		//////////////////////////
		//ALGEBRA
		//////////////////////////
		static T length(const Vector4<T>& vec) noexcept
		{
			return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
		}
		T length() const noexcept
		{
			return Vector4<T>::length(*this);
		}
		static Vector4<T> normalize(const Vector4<T>& vec) noexcept
		{
			T l = Vector4<T>::length(vec);
			return Vector4<T>(vec.x / l, vec.y / l, vec.z / l, vec.w / l);
		}
		void normalize() noexcept
		{
			*this = Vector4<T>::normalize(*this);
		}
		static T dot(const Vector4<T>& vec1, const Vector4<T>& vec2) noexcept
		{
			return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z + vec1.w * vec2.w);
		}
		T dot(const Vector4<T>& vec) noexcept
		{
			return (x * vec.x + y * vec.y + z * vec.z + w * vec.w);
		}
		
		////////////////////
		//UTILITY
		////////////////////
		friend std::ostream& operator<<(std::ostream& out, const Vector4<T>& vec)
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

	using Vector4f = Vector4<float>;
	using Vector4u = Vector4<unsigned>;
	using Vector4i = Vector4<int>;
	using Vector4d = Vector4<double>;
}


