#pragma once

///////////////////////////////////
//Headers
///////////////////////////////////
#include <Core/Export.hpp>
#include <Core/Math/Vector.hpp>

namespace ax
{
	///////////////////////////////////
	//Matrix
	///////////////////////////////////
	template<typename T>
	class AXION_CORE_API Matrix4
	{
	public:
		inline Matrix4<T>()
		{
			
		}
		inline Matrix4<T>(T x1, T y1, T z1, T w1,
							T x2, T y2, T z2, T w2,
							T x3, T y3, T z3, T w3,
							T x4, T y4, T z4, T w4)
		{
			m[0][0] = x1;
			m[0][1] = y1;
			m[0][2] = z1;
			m[0][3] = w1;
			
			m[1][0] = x2;
			m[1][1] = y2;
			m[1][2] = z2;
			m[1][3] = w2;
			
			m[2][0] = x3;
			m[2][1] = y3;
			m[2][2] = z3;
			m[2][3] = w3;
			
			m[3][0] = x4;
			m[3][1] = y4;
			m[3][2] = z4;
			m[3][3] = w4;
		}
		inline Matrix4<T>(Vector4<T> vec1,
							Vector4<T> vec2,
							Vector4<T> vec3,
							Vector4<T> vec4)
		{
			m[0][0] = vec1.x;
			m[0][1] = vec1.y;
			m[0][2] = vec1.z;
			m[0][3] = vec1.w;
			
			m[1][0] = vec2.x;
			m[1][1] = vec2.y;
			m[1][2] = vec2.z;
			m[1][3] = vec2.w;
			
			m[2][0] = vec3.x;
			m[2][1] = vec3.y;
			m[2][2] = vec3.z;
			m[2][3] = vec3.w;
			
			m[3][0] = vec4.x;
			m[3][1] = vec4.y;
			m[3][2] = vec4.z;
			m[3][3] = vec4.w;
		}
		
		//////////////////////////
		//OPERATORS
		//////////////////////////
		inline Matrix4<T> operator*(const Matrix4<T>& mat)
		{
			Matrix4<T> result;
			for(uint i = 0; i < 4; i++)
			{
				for(uint j = 0; j < 4; j++)
				{
					for(uint k = 0; k < 4; k++)
					{
						result.m[i][j] += m[i][k] * mat.m[k][j]; 
					}
				}
			}
			
			return result;
		}
		inline Vector4<T> operator*(const Vector4<T>& vec)
		{
			return Vector4<T>(
				m[0][0] * vec.x + m[0][1] * vec.y + m[0][2] * vec.z + m[0][3] * vec.w,
				m[1][0] * vec.x + m[1][1] * vec.y + m[1][2] * vec.z + m[1][3] * vec.w,
				m[2][0] * vec.x + m[2][1] * vec.y + m[2][2] * vec.z + m[2][3] * vec.w,
				m[3][0] * vec.x + m[3][1] * vec.y + m[3][2] * vec.z + m[3][3] * vec.w
			);
		}
		
		//////////////////////////
		//ALGEBRA
		//////////////////////////
		inline static Matrix4<T> identity()
		{
			return Matrix4<T>(1, 0, 0, 0,
								0, 1, 0, 0,
								0, 0, 1, 0,
								0, 0, 0, 1);
		}
		inline static Matrix4<T> translate(T x, T y, T z)
		{
			return Matrix4<T>(1, 0, 0, x,
								0, 1, 0, y,
								0, 0, 1, z,
								0, 0, 0, 1);
		}
		inline static Matrix4<T> rotate(T x, T y, T z)
		{
			Matrix4<T> trans = Matrix4<T>::identity();
			if(x != 0)
			{
				trans = Matrix4<T>::rotateX(x) * trans;
			}
			if(y != 0)
			{
				trans = Matrix4<T>::rotateY(y) * trans;
			}
			if(z != 0)
			{
				trans = Matrix4<T>::rotateZ(z) * trans;
			}
								
			return trans;
		}
		inline static Matrix4<T> rotateX(T x)
		{
			return Matrix4<T>(1,  0,            0,           0,
								0, std::cos(x), -std::sin(x), 0,
								0, std::sin(x),  std::cos(x), 0,
								0, 0,            0,           1);
		}
		inline static Matrix4<T> rotateY(T y)
		{
			return Matrix4<T>(std::cos(y),   0, std::sin(y), 0,
								0,            1, 0,           0,
								-std::sin(y), 0, std::cos(y), 0,
								0,            0, 0,           1);
		}
		inline static Matrix4<T> rotateZ(T z)
		{
			return Matrix4<T>(std::cos(z),  -std::sin(z), 0, 0,
								std::sin(z),  std::cos(z), 0, 0,
								0,            0,           1, 0,
								0,            0,           0, 1);
		}
		inline static Matrix4<T> scale(T x, T y, T z)
		{
			return Matrix4<T>(Vector4<T>(x, 0, 0, 0),
								Vector4<T>(0, y, 0, 0),
								Vector4<T>(0, 0, z, 0),
								Vector4<T>(0, 0, 0, 1));
		}
		
		//////////////////////////
		//UTILITY
		//////////////////////////
		inline friend std::ostream& operator<<(std::ostream& out, const Matrix4<T>& mat)
		{
			for(uint y = 0; y < 4; y++)
			{
				out << "{";
				for(uint x = 0; x < 4; x++)
				{
					out << " " << mat.m[y][x] << " "; 
				}
				out << "}" << std::endl;
			}
			
			return out;
		}
		
		
	private:
		T m[4][4] = {{0}}; //[columns = y][columns = x]
	};

	typedef Matrix4<float> Matrix4f;
	typedef Matrix4<double> Matrix4d;
}

