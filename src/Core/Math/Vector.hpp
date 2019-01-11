#pragma once

///////////////////////////////////
//Headers
///////////////////////////////////
#include <Core/Export.hpp>

#include <iostream>
#include <cmath>

namespace ax
{
	template<typename T>
	class AXION_CORE_API Vector2;
	template<typename T>
	class AXION_CORE_API Vector3;
	template<typename T>
	class AXION_CORE_API Vector4;

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
		Vector2<T> operator+(const Vector2<T>& vec)const{return Vector2<T>(x + vec.x, y + vec.y);}
		Vector2<T> operator-(const Vector2<T>& vec)const{return Vector2<T>(x - vec.x, y - vec.y);}
		Vector2<T> operator*(const Vector2<T>& vec)const{return Vector2<T>(x * vec.x, y * vec.y);}
		Vector2<T> operator*(const T& factor)const{return Vector2<T>(x * factor, y * factor);}
		Vector2<T> operator/(const Vector2<T>& vec)const{return Vector2<T>(x / vec.x, y / vec.y);}
		Vector2<T> operator+=(const Vector2<T>& vec){x += vec.x; y += vec.y; return *this;}
		Vector2<T> operator-=(const Vector2<T>& vec){x -= vec.x; y -= vec.y; return *this;}
		Vector2<T> operator*=(const Vector2<T>& vec){x *= vec.x; y *= vec.y; return *this;}
		Vector2<T> operator/=(const Vector2<T>& vec){x /= vec.x; y /= vec.y; return *this;}
		
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

		const T* data() const noexcept
		{
			return &x;
		}
		
	public:
		T x = 0;
		T y = 0;
	};

	////////////////////////
	//COMMUTATIVE OPERATORS
	////////////////////////
	template<typename T>
	Vector2<T> operator*(const T& k, const Vector2<T>& vec){return Vector2<T>(vec.x * k, vec.y * k);}
	template<typename T>
	Vector2<T> operator*(const Vector2<T>& vec, const T& k){return k * vec;}

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
		Vector3<T>(const Vector4<T>& vec)
		{
			this->x = vec.x;
			this->y = vec.y;
			this->z = vec.z;
		}
		
		////////////////////
		//OPERATORS
		////////////////////
		Vector3<T> operator+(const Vector3<T> vec)const{return Vector3<T>(x + vec.x, y + vec.y, z + vec.z);}
		Vector3<T> operator-(const Vector3<T> vec)const{return Vector3<T>(x - vec.x, y - vec.y, z - vec.z);}
		Vector3<T> operator*(const Vector3<T> vec)const{return Vector3<T>(x * vec.x, y * vec.y, z * vec.z);}
		Vector3<T> operator*(const T& factor)const{return Vector3<T>(x * factor, y * factor, z * factor);}
		Vector3<T> operator/(const Vector3<T> vec)const{return Vector3<T>(x / vec.x, y / vec.y, z / vec.z);}
		Vector3<T> operator+=(const Vector3<T>& vec){x += vec.x; y += vec.y; z += vec.z; return *this;}
		Vector3<T> operator-=(const Vector3<T>& vec){x -= vec.x; y -= vec.y; z -= vec.z; return *this;}
		Vector3<T> operator*=(const Vector3<T>& vec){x *= vec.x; y *= vec.y; z *= vec.z; return *this;}
		Vector3<T> operator/=(const Vector3<T>& vec){x /= vec.x; y /= vec.y; z /= vec.z; return *this;}

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
			if(l != 0) return Vector3<T>(vec.x / l, vec.y / l, vec.z / l);
			return vec;
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

		const T* data() const noexcept
		{
			return &x;
		}

		static const Vector3<T> forward;
		static const Vector3<T> backward;
		static const Vector3<T> left;
		static const Vector3<T> right;
		static const Vector3<T> up;
		static const Vector3<T> down;
		
	public:
		T x = 0;
		T y = 0;
		T z = 0;
	};

	////////////////////////
	//COMMUTATIVE OPERATORS
	////////////////////////
	template<typename T>
	Vector3<T> operator*(const T& k, const Vector3<T>& vec){return Vector3<T>(vec.x * k, vec.y * k, vec.z * k);}
	template<typename T>
	Vector3<T> operator*(const Vector3<T>& vec, const T& k){return k * vec;}

	//////////////
	//ENGINE AXIS
	//////////////
	template<typename T>
	const Vector3<T> Vector3<T>::forward = Vector3<T>(0, 0, 1);
	template<typename T>
	const Vector3<T> Vector3<T>::backward = Vector3<T>(0, 0, -1);
	template<typename T>
	const Vector3<T> Vector3<T>::left = Vector3<T>(1, 0, 0);
	template<typename T>
	const Vector3<T> Vector3<T>::right = Vector3<T>(-1, 0, 0);
	template<typename T>
	const Vector3<T> Vector3<T>::up = Vector3<T>(0, 1, 0);
	template<typename T>
	const Vector3<T> Vector3<T>::down = Vector3<T>(0, -1, 0);

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
		Vector4<T> operator+(const Vector4<T> vec)const{return Vector4<T>(x + vec.x, y + vec.y, z + vec.z, w + vec.w);}
		Vector4<T> operator-(const Vector4<T> vec)const{return Vector4<T>(x - vec.x, y - vec.y, z - vec.z, w - vec.w);}
		Vector4<T> operator*(const Vector4<T> vec)const{return Vector4<T>(x * vec.x, y * vec.y, z * vec.z, w * vec.w);}
		Vector4<T> operator/(const Vector4<T> vec)const{return Vector4<T>(x / vec.x, y / vec.y, z / vec.z, w / vec.w);}
		Vector4<T> operator+=(const Vector4<T>& vec){x += vec.x; y += vec.y; z += vec.z; w += vec.w; return *this;}
		Vector4<T> operator-=(const Vector4<T>& vec){x -= vec.x; y -= vec.y; z -= vec.z; w -= vec.w; return *this;}
		Vector4<T> operator*=(const Vector4<T>& vec){x *= vec.x; y *= vec.y; z *= vec.z; w *= vec.w; return *this;}
		Vector4<T> operator/=(const Vector4<T>& vec){x /= vec.x; y /= vec.y; z /= vec.z; w /= vec.w; return *this;}
		
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

		const T* data() const noexcept
		{
			return &x;
		}
		
	public:
		T x = 0;
		T y = 0;
		T z = 0;
		T w = 0;
	};

	////////////////////////
	//COMMUTATIVE OPERATORS
	////////////////////////
	template<typename T>
	Vector4<T> operator*(const T& k, const Vector4<T>& vec){return Vector4<T>(vec.x * k, vec.y * k, vec.z * k, vec.w * k);}
	template<typename T>
	Vector4<T> operator*(const Vector4<T>& vec, const T& k){return k * vec;}

	using Vector4f = Vector4<float>;
	using Vector4u = Vector4<unsigned>;
	using Vector4i = Vector4<int>;
	using Vector4d = Vector4<double>;
}


