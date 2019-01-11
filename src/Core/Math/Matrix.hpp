#pragma once

///////////////////////////////////
//Headers
///////////////////////////////////
#include <Core/Export.hpp>
#include <Core/Math/Math.hpp>
#include <Core/Math/Vector.hpp>

namespace ax
{
	///////////////////////////////////
	//Matrix 4x4
	///////////////////////////////////
	template<typename T>
	class AXION_CORE_API Matrix4
	{
	public:
		Matrix4<T>(){}
		Matrix4<T>(T x1, T y1, T z1, T w1,
					T x2, T y2, T z2, T w2,
					T x3, T y3, T z3, T w3,
					T x4, T y4, T z4, T w4)
		{
			m[0][0] = x1;
			m[1][0] = y1;
			m[2][0] = z1;
			m[3][0] = w1;
			
			m[0][1] = x2;
			m[1][1] = y2;
			m[2][1] = z2;
			m[3][1] = w2;
			
			m[0][2] = x3;
			m[1][2] = y3;
			m[2][2] = z3;
			m[3][2] = w3;
			
			m[0][3] = x4;
			m[1][3] = y4;
			m[2][3] = z4;
			m[3][3] = w4;
		}
		Matrix4<T>(Vector4<T> vec1,
					Vector4<T> vec2,
					Vector4<T> vec3,
					Vector4<T> vec4)
		{
			m[0][0] = vec1.x;
			m[1][0] = vec1.y;
			m[2][0] = vec1.z;
			m[3][0] = vec1.w;
			
			m[0][1] = vec2.x;
			m[1][1] = vec2.y;
			m[2][1] = vec2.z;
			m[3][1] = vec2.w;
			
			m[0][2] = vec3.x;
			m[1][2] = vec3.y;
			m[2][2] = vec3.z;
			m[3][2] = vec3.w;
			
			m[0][3] = vec4.x;
			m[1][3] = vec4.y;
			m[2][3] = vec4.z;
			m[3][3] = vec4.w;
		}
		
		//////////////////////////
		//OPERATORS
		//////////////////////////
		Matrix4<T> operator*(const Matrix4<T>& mat) const
		{
			Matrix4<T> result;
			for(unsigned i = 0; i < 4; i++)
			{
				for(unsigned j = 0; j < 4; j++)
				{
					for(unsigned k = 0; k < 4; k++)
					{
						result.m[j][i] += m[k][i] * mat.m[j][k]; 
					}
				}
			}
			
			return result;
		}
		Vector4<T> operator*(const Vector4<T>& vec) const
		{
			return Vector4<T>(
				m[0][0] * vec.x + m[1][0] * vec.y + m[2][0] * vec.z + m[3][0] * vec.w,
				m[0][1] * vec.x + m[1][1] * vec.y + m[2][1] * vec.z + m[3][1] * vec.w,
				m[0][2] * vec.x + m[1][2] * vec.y + m[2][2] * vec.z + m[3][2] * vec.w,
				m[0][3] * vec.x + m[1][3] * vec.y + m[2][3] * vec.z + m[3][3] * vec.w
			);
		}
		Vector3<T> operator*(const Vector3<T>& vec) const
		{
			return Vector3<T>(
				m[0][0] * vec.x + m[1][0] * vec.y + m[2][0] * vec.z + m[3][0],
				m[0][1] * vec.x + m[1][1] * vec.y + m[2][1] * vec.z + m[3][1],
				m[0][2] * vec.x + m[1][2] * vec.y + m[2][2] * vec.z + m[3][2]
			);
		}
		
		//////////////////////////
		//ALGEBRA
		//////////////////////////
		static Matrix4<T> identity() noexcept
		{
			return Matrix4<T>(1, 0, 0, 0,
								0, 1, 0, 0,
								0, 0, 1, 0,
								0, 0, 0, 1);
		}
		static Matrix4<T> translate(T x, T y, T z) noexcept
		{
			return Matrix4<T>(1, 0, 0, x,
								0, 1, 0, y,
								0, 0, 1, z,
								0, 0, 0, 1);
		}
		static Matrix4<T> translate(const Vector3<T>& translation) noexcept
		{
			return Matrix4<T>::translate(translation.x, translation.y, translation.z);
		}
		static Matrix4<T> rotate(T x, T y, T z) noexcept
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
		static Matrix4<T> rotate(const Vector3<T>& rotation) noexcept
		{
			return Matrix4<T>::rotate(rotation.x, rotation.y, rotation.z);
		}
		static Matrix4<T> rotateX(T x) noexcept
		{
			return Matrix4<T>(1,  0,            0,           0,
								0, std::cos(x), -std::sin(x), 0,
								0, std::sin(x),  std::cos(x), 0,
								0, 0,            0,           1);
		}
		static Matrix4<T> rotateY(T y) noexcept
		{
			return Matrix4<T>(std::cos(y),   0, std::sin(y), 0,
								0,            1, 0,           0,
								-std::sin(y), 0, std::cos(y), 0,
								0,            0, 0,           1);
		}
		static Matrix4<T> rotateZ(T z) noexcept
		{
			return Matrix4<T>(std::cos(z),  -std::sin(z), 0, 0,
								std::sin(z),  std::cos(z), 0, 0,
								0,            0,           1, 0,
								0,            0,           0, 1);
		}
		static Matrix4<T> scale(T x, T y, T z) noexcept
		{
			return Matrix4<T>(Vector4<T>(x, 0, 0, 0),
								Vector4<T>(0, y, 0, 0),
								Vector4<T>(0, 0, z, 0),
								Vector4<T>(0, 0, 0, 1));
		}
		static Matrix4<T> scale(const Vector3<T>& scale) noexcept
		{
			return Matrix4<T>::scale(scale.x, scale.y, scale.z);
		}
		static Matrix4<T> lookAt(Vector3<T>& eye, Vector3<T>& target, Vector3<T>& up) noexcept
		{
			Vector3<T> zaxis = Vector3<T>::normalize(eye - target);
			Vector3<T> xaxis = Vector3<T>::normalize(Vector3<T>::cross(up, zaxis));
			Vector3<T> yaxis = Vector3<T>::cross(zaxis, xaxis);

			return Matrix4<T>(
				xaxis.x, xaxis.y, xaxis.z, -Vector3<T>::dot(xaxis, eye),
				yaxis.x, yaxis.y, yaxis.z, -Vector3<T>::dot(yaxis, eye),
				zaxis.x, zaxis.y, zaxis.z, -Vector3<T>::dot(zaxis, eye),
				0, 0, 0, 1
			);
		}
		static Matrix4<T> perspective(T fov = 90, T aspect = 1, T near = 0.01, T far = 100) noexcept
		{
			T yS = (T)1 / tan(radians(fov) / (T)2);
			T xS = yS / aspect;
			T nmf = near - far;

			return Matrix4<T>(
				xS, 0, 0, 0,
				0, yS, 0, 0,
				0, 0, (far + near) / nmf, 2 * far * near / nmf,
				0, 0, -1, 0
			);
		}

		void inverse() noexcept
		{
			// Inversion by LU decomposition, alternate implementation
			int i, j, k;

			for (i = 1; i < 4; i++)
			{
				m[i][0] /= m[0][0];
			}

			for (i = 1; i < 4; i++)
			{
				for (j = i; j < 4; j++)
				{
					T sum = 0.0;
					for (k = 0; k < i; k++)
					{
						sum += m[k][j] * m[i][k];
					}
					m[i][j] -= sum;
				}
				if (i == 4 - 1) continue;
				for (j = i + 1; j < 4; j++)
				{
					T sum = 0.0;
					for (int k = 0; k < i; k++)
						sum += m[k][i] * m[j][k];
					m[j][i] = (m[j][i] - sum) / m[i][i];
				}
			}

			//Invert L
			for (i = 0; i < 4; i++)
			{
				for (int j = i; j < 4; j++)
				{
					T x = 1.0;
					if (i != j)
					{
						x = 0.0;
						for (int k = i; k < j; k++) 
							x -= m[k][j] * m[i][k];
					}
					m[i][j] = x / m[j][j];
				}
			}

			//Invert U
			for (i = 0; i < 4; i++)
			{
				for (j = i; j < 4; j++)
				{
					if (i == j) continue;
					T sum = 0.0;
					for (int k = i; k < j; k++)
						sum += m[j][k] * ((i == k) ? 1.0f : m[k][i]);
					m[j][i] = -sum;
				}
			}

			//Final Inversion
			for (i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					T sum = 0.0;
					for (int k = ((i > j) ? i : j); k < 4; k++)  
						sum += ((j == k) ? 1.0f : m[k][j]) * m[i][k];
					m[i][j] = sum;
				}
			}
		}
		static Matrix4<T> inverse(const Matrix4<T>& matrix) noexcept
		{
			Matrix4<T> m = matrix;
			m.inverse();

			return m;
		}
		void transpose() noexcept
		{
			Matrix4<T> mat = *this;

			for(unsigned y = 0; y < 4; y++)
				for(unsigned x = 0; x < 4; x++)
				{
					m[x][y] = mat.m[y][x];	
				}
		}
		static Matrix4<T> transpose(const Matrix4<T>& matrix) noexcept
		{
			Matrix4<T> m = matrix;
			m.transpose();

			return m;
		}
		//////////////////////////
		//UTILITY
		//////////////////////////
		friend std::ostream& operator<<(std::ostream& out, const Matrix4<T>& mat)
		{
			for(unsigned y = 0; y < 4; y++)
			{
				out << "{";
				for(unsigned x = 0; x < 4; x++)
				{
					out << " " << mat.m[y][x] << " "; 
				}
				out << "}" << std::endl;
			}
			
			return out;
		}

		const T* data() const noexcept
		{
			return &m[0][0];
		}
		
	public:
		T m[4][4] = {{0}}; //[columns = y][columns = x] (columns major)
	};

	using Matrix4f = Matrix4<float>;
	using Matrix4d = Matrix4<double>;

	///////////////////////////////////
	//Matrix 3x3
	///////////////////////////////////
	template<typename T>
	class AXION_CORE_API Matrix3
	{
	public:
		Matrix3<T>(){}
		Matrix3<T>(T x1, T y1, T z1,
					T x2, T y2, T z2,
					T x3, T y3, T z3
				  )
		{
			m[0][0] = x1;
			m[1][0] = y1;
			m[2][0] = z1;
			
			m[0][1] = x2;
			m[1][1] = y2;
			m[2][1] = z2;
			
			m[0][2] = x3;
			m[1][2] = y3;
			m[2][2] = z3;
		}
		Matrix3<T>(Vector3<T> vec1,
					Vector3<T> vec2,
					Vector3<T> vec3)
		{
			m[0][0] = vec1.x;
			m[1][0] = vec1.y;
			m[2][0] = vec1.z;
			
			m[0][1] = vec2.x;
			m[1][1] = vec2.y;
			m[2][1] = vec2.z;
			
			m[0][2] = vec3.x;
			m[1][2] = vec3.y;
			m[2][2] = vec3.z;
		}
		Matrix3<T>(const Matrix4<T>& mat)
		{
			m[0][0] = mat.m[0][0];
			m[1][0] = mat.m[1][0];
			m[2][0] = mat.m[2][0];
			
			m[0][1] = mat.m[0][1];
			m[1][1] = mat.m[1][1];
			m[2][1] = mat.m[2][1];
			
			m[0][2] = mat.m[0][2];
			m[1][2] = mat.m[1][2];
			m[2][2] = mat.m[2][2];
		}
		
		//////////////////////////
		//OPERATORS
		//////////////////////////
		Matrix3<T> operator*(const Matrix3<T>& mat) noexcept
		{
			Matrix3<T> result;
			for(unsigned i = 0; i < 3; i++)
			{
				for(unsigned j = 0; j < 3; j++)
				{
					for(unsigned k = 0; k < 3; k++)
					{
						result.m[j][i] += m[k][i] * mat.m[j][k]; 
					}
				}
			}
			
			return result;
		}
		Vector3<T> operator*(const Vector3<T>& vec) noexcept
		{
			return Vector4<T>(
				m[0][0] * vec.x + m[1][0] * vec.y + m[2][0] * vec.z,
				m[0][1] * vec.x + m[1][1] * vec.y + m[2][1] * vec.z,
				m[0][2] * vec.x + m[1][2] * vec.y + m[2][2] * vec.z
			);
		}
		Vector2<T> operator*(const Vector2<T>& vec) noexcept
		{
			return Vector2<T>(
				m[0][0] * vec.x + m[1][0] * vec.y,
				m[0][1] * vec.x + m[1][1] * vec.y
			);
		}
		
		//////////////////////////
		//ALGEBRA
		//////////////////////////
		static Matrix3<T> identity() noexcept
		{
			return Matrix3<T>(1, 0, 0,
								0, 1, 0,
								0, 0, 1);
		}

		void inverse() noexcept
		{
			T det = m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) -
             		m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
             		m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);

			T invdet = 1 / det;

			Matrix3<T> minv;
			minv.m[0][0] = (m[1][1] * m[2][2] - m[2][1] * m[1][2]) * invdet;
			minv.m[0][1] = (m[0][2] * m[2][1] - m[0][1] * m[2][2]) * invdet;
			minv.m[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * invdet;
			minv.m[1][0] = (m[1][2] * m[2][0] - m[1][0] * m[2][2]) * invdet;
			minv.m[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]) * invdet;
			minv.m[1][2] = (m[1][0] * m[0][2] - m[0][0] * m[1][2]) * invdet;
			minv.m[2][0] = (m[1][0] * m[2][1] - m[2][0] * m[1][1]) * invdet;
			minv.m[2][1] = (m[2][0] * m[0][1] - m[0][0] * m[2][1]) * invdet;
			minv.m[2][2] = (m[0][0] * m[1][1] - m[1][0] * m[0][1]) * invdet;

			*this = minv;
		}
		static Matrix3<T> inverse(const Matrix3<T>& matrix) noexcept
		{
			Matrix3<T> m = matrix;
			m.inverse();

			return m;
		}
		void transpose() noexcept
		{
			Matrix3<T> mat = *this;

			for(unsigned y = 0; y < 3; y++)
				for(unsigned x = 0; x < 3; x++)
				{
					m[x][y] = mat.m[y][x];	
				}
		}
		static Matrix3<T> transpose(const Matrix3<T>& matrix) noexcept
		{
			Matrix3<T> m = matrix;
			m.transpose();

			return m;
		}

		//////////////////////////
		//UTILITY
		//////////////////////////
		friend std::ostream& operator<<(std::ostream& out, const Matrix3<T>& mat)
		{
			for(unsigned y = 0; y < 3; y++)
			{
				out << "{";
				for(unsigned x = 0; x < 3; x++)
				{
					out << " " << mat.m[y][x] << " "; 
				}
				out << "}" << std::endl;
			}
			
			return out;
		}

		const T* data() const noexcept
		{
			return &m[0][0];
		}
		
	public:
		T m[3][3] = {{0}}; //[columns = y][columns = x] (columns major)
	};

	using Matrix3f = Matrix3<float>;
	using Matrix3d = Matrix3<double>;
}



