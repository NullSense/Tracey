#pragma once
#define _USE_MATH_DEFINES
#include "Globals.h"
#include <algorithm>
#include <cmath>

//template<typename T>
struct Vector3
{
public:
	FPType x, y, z;

	Vector3(const FPType x_, const FPType y_, const FPType z_);
	Vector3(const FPType value);
	Vector3();

	Vector3 Normalize();
	FPType Magnitude();
	FPType Dot(const Vector3 &v) const;
	Vector3 Cross(const Vector3 &v) const;
	Vector3 operator-() const;

	inline Vector3 operator*(const Vector3 &v) const;
	Vector3 operator*(const FPType s) const;
	inline Vector3 operator*=(const FPType s);
	inline Vector3 operator/(const FPType s) const;
	Vector3 operator/(const Vector3 &v) const;
	Vector3 operator-(const Vector3 &v) const;
	Vector3 operator+(const Vector3 &v) const;

	const FPType& operator [] (uint8_t i) const
	{
		return (&x)[i];
	}
	FPType& operator [] (uint8_t i)
	{
		return (&x)[i];
	}

	FPType clamp1(const FPType lo, const FPType hi, const FPType v);

	Vector3 SphericalToCartesian(const FPType theta, const FPType phi);
	inline FPType SphericalTheta(const Vector3 &v);
	inline FPType SphericalPhi(const Vector3 &v);
	inline FPType cosTheta(const Vector3 &w)
	{
		return w[2];
	}
	inline FPType sinTheta2(const Vector3 &w)
	{
		return std::max(FPType(0), 1 - cosTheta(w) * cosTheta(w));
	}
	inline FPType sinTheta(const Vector3 &w)
	{
		return sqrt(sinTheta2(w));
	}
	inline FPType cosPhi(const Vector3 &w)
	{
		FPType sintheta = sinTheta(w);
		if(sintheta == 0) return 1;
		return clamp1(w[0] / sintheta, -1, 1);
	}
	inline FPType sinPhi(const Vector3 &w)
	{
		FPType sintheta = sinTheta(w);
		if(sintheta == 0) return 0;
		return clamp1(w[1] / sintheta, -1, 1);
	}
};

typedef Vector3 Vec3f;