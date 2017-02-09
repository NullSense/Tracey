#pragma once

#include "Globals.h"
#include "Vector.h"

template<typename T>
class Matrix44
{
public:
	T x[4][4] = {{1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1}}; // Identity matrix

	Matrix44()
	{}

	Matrix44(T a, T b, T c, T d, T e, T f, T g, T h,
			 T i, T j, T k, T l, T m, T n, T o, T p)
	{
		x[0][0] = a;
		x[0][1] = b;
		x[0][2] = c;
		x[0][3] = d;
		x[1][0] = e;
		x[1][1] = f;
		x[1][2] = g;
		x[1][3] = h;
		x[2][0] = i;
		x[2][1] = j;
		x[2][2] = k;
		x[2][3] = l;
		x[3][0] = m;
		x[3][1] = n;
		x[3][2] = o;
		x[3][3] = p;
	}

	const T* operator [] (uint8_t i) const
	{
		return x[i];
	}
	T* operator [] (uint8_t i)
	{
		return x[i];
	}

	Matrix44<T> operator*(const Matrix44<T> &rhs) const
	{
		// Multiply the current matrix with another matrix (rhs)
		Matrix44 tmp;
		Multiply(*this, rhs, tmp);

		return tmp;
	}

	static void Multiply(const Matrix44<T> &a, const Matrix44 &b, Matrix44 &c)
	{
		for(unsigned i = 0; i < 4; ++i)
		{
			for(unsigned j = 0; j < 4; ++j)
			{
				c[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] +
					a[i][2] * b[2][j] + a[i][3] * b[3][j];
			}
		}
	}
	//void MultVecMatrix(const Vector &src, Vector &dst) const;
	void MultVecMatrix(const Vector &src, Vector &dst) const
	{
		FPType a, b, c, w;

		a = src[0] * x[0][0] + src[1] * x[1][0] + src[2] * x[2][0] + x[3][0];
		b = src[0] * x[0][1] + src[1] * x[1][1] + src[2] * x[2][1] + x[3][1];
		c = src[0] * x[0][2] + src[1] * x[1][2] + src[2] * x[2][2] + x[3][2];
		w = src[0] * x[0][3] + src[1] * x[1][3] + src[2] * x[2][3] + x[3][3];

		dst.x = a / w;
		dst.y = b / w;
		dst.z = c / w;
	}

	Matrix44<T> Inverse()
	{
		int i, j, k;
		Matrix44 s;
		Matrix44 t(*this);

		// Forward elimination
		for(i = 0; i < 3; i++)
		{
			int pivot = i;

			T pivotsize = t[i][i];

			if(pivotsize < 0)
				pivotsize = -pivotsize;

			for(j = i + 1; j < 4; j++)
			{
				T tmp = t[j][i];

				if(tmp < 0)
					tmp = -tmp;

				if(tmp > pivotsize)
				{
					pivot = j;
					pivotsize = tmp;
				}
			}

			if(pivotsize == 0)
			{
				// Cannot invert singular matrix
				return Matrix44();
			}

			if(pivot != i)
			{
				for(j = 0; j < 4; j++)
				{
					T tmp;

					tmp = t[i][j];
					t[i][j] = t[pivot][j];
					t[pivot][j] = tmp;

					tmp = s[i][j];
					s[i][j] = s[pivot][j];
					s[pivot][j] = tmp;
				}
			}

			for(j = i + 1; j < 4; j++)
			{
				T f = t[j][i] / t[i][i];

				for(k = 0; k < 4; k++)
				{
					t[j][k] -= f * t[i][k];
					s[j][k] -= f * s[i][k];
				}
			}
		}

		// Backward substitution
		for(i = 3; i >= 0; --i)
		{
			T f;

			if((f = t[i][i]) == 0)
			{
				// Cannot invert singular matrix
				return Matrix44();
			}

			for(j = 0; j < 4; j++)
			{
				t[i][j] /= f;
				s[i][j] /= f;
			}

			for(j = 0; j < i; j++)
			{
				f = t[j][i];

				for(k = 0; k < 4; k++)
				{
					t[j][k] -= f * t[i][k];
					s[j][k] -= f * s[i][k];
				}
			}
		}

		return s;
	}

	void MultDirMatrix(const Vector &src, Vector &dst) const
	{
		dst.x = src.x * x[0][0] + src.y * x[1][0] + src.z * x[2][0];
		dst.y = src.x * x[0][1] + src.y * x[1][1] + src.z * x[2][1];
		dst.z = src.x * x[0][2] + src.y * x[1][2] + src.z * x[2][2];
	}

	Matrix44<T> Transpose() const
	{
		Matrix44 transpMat;
		for(unsigned i = 0; i < 4; ++i)
		{
			for(unsigned j = 0; j < 4; ++j)
			{
				transpMat[i][j] = x[j][i];
			}
		}

		return transpMat;
	}
	Matrix44<T> LookAt(const Vector& from, const Vector& to, const Vector& tmp = Vector(0, 1, 0))
	{
		Vec3f forward = normalize(from - to);
		Vec3f right = crossProduct(normalize(tmp), forward);
		Vec3f up = crossProduct(forward, right);

		Matrix44 camToWorld;

		camToWorld[0][0] = right.x;
		camToWorld[0][1] = right.y;
		camToWorld[0][2] = right.z;
		camToWorld[1][0] = up.x;
		camToWorld[1][1] = up.y;
		camToWorld[1][2] = up.z;
		camToWorld[2][0] = forward.x;
		camToWorld[2][1] = forward.y;
		camToWorld[2][2] = forward.z;

		camToWorld[3][0] = from.x;
		camToWorld[3][1] = from.y;
		camToWorld[3][2] = from.z;

		return camToWorld;
	}
};

typedef Matrix44<float> Matrix44f;
typedef Matrix44<double> Matrix44d;