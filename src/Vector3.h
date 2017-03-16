#pragma once
#define _USE_MATH_DEFINES
#include "Globals.h"
#include <algorithm>
#include <cmath>

template<typename T>
struct Vector3
{
public:
	T x, y, z;

	Vector3<T>(const T x_, const T y_, const T z_)
	{
		x = x_;
		y = y_;
		z = z_;
	}
	Vector3<T>(const T value)
	{
		x = value;
		y = value;
		z = value;
	}
	Vector3<T>()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	inline Vector3<T> Normalize()
	{
		T length = Dot(*this);
		if(length > 0)
		{
			T invLength = 1 / sqrt(length);
			x *= invLength, y *= invLength, z *= invLength;
		}
		return *this;
	}
	inline T Magnitude()
	{
		return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	}
	inline T Dot(const Vector3<T> &v) const
	{
		return (this->x * v.x + this->y * v.y + this->z * v.z);
	}
	inline Vector3<T> Cross(const Vector3<T> &v) const
	{
		return Vector3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
	}
	inline Vector3<T> operator-() const
	{
		return Vector3(-x, -y, -z);
	}

	inline Vector3<T> operator*(const Vector3<T> &v) const
	{
		return Vector3(x * v.x, y * v.y, z * v.z);
	}
	inline Vector3<T> operator*(const T s) const
	{
		return Vector3(x * s, y * s, z * s);
	}
	inline Vector3<T> operator*=(const T s)
	{
		x *= s, y *= s, z *= s;
		return *this;
	}
	inline Vector3<T> operator/(const T s) const
	{
		return Vector3(x / s, y / s, z / s);
	}
	inline Vector3<T> operator/(const Vector3<T> &v) const
	{
		return Vector3(x / v.x, y / v.y, z / v.z);
	}
	inline Vector3<T> operator-(const Vector3<T> &v) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}
	inline Vector3 operator+(const Vector3 &v) const
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	const T& operator [] (uint8_t i) const
	{
		return (&x)[i];
	}
	T& operator [] (uint8_t i)
	{
		return (&x)[i];
	}

	inline Vector3<T> SphericalToCartesian(const T theta, const T phi)
	{
		return Vector3(cos(phi) * sin(theta), sin(phi) * sin(theta), cos(theta));
	}
	inline T SphericalTheta(const Vector3<T> &v)
	{
		return acos(clamp1(v[2], -1, 1));
	}
	inline T SphericalPhi(const Vector3<T> &v)
	{
		T p = atan2(v[1], v[0]);
		return (p < 0) ? p + 2 * M_PI : p;
	}
	inline T cosTheta(const Vector3<T> &w)
	{
		return w[2];
	}
	inline T sinTheta2(const Vector3<T> &w)
	{
		return std::max(T(0), 1 - cosTheta(w) * cosTheta(w));
	}
	inline T sinTheta(const Vector3<T> &w)
	{
		return sqrt(sinTheta2(w));
	}
	inline T cosPhi(const Vector3<T> &w)
	{
		T sintheta = sinTheta(w);
		if(sintheta == 0) return 1;
		return clamp1(w[0] / sintheta, -1, 1);
	}
	inline T sinPhi(const Vector3<T> &w)
	{
		T sintheta = sinTheta(w);
		if(sintheta == 0) return 0;
		return clamp1(w[1] / sintheta, -1, 1);
	}
};

typedef Vector3<double> Vec3d;
typedef Vector3<double> Vector3d;