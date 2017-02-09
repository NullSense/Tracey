#pragma once
#define _USE_MATH_DEFINES
#include "Globals.h"
#include <algorithm>
#include <cmath>

struct Vector
{
public:
	FPType x, y, z;

	Vector(FPType x_, FPType y_, FPType z_);
	Vector();

	Vector Normalize();
	FPType Magnitude();
	FPType Dot(const Vector &v);
	Vector Cross(const Vector &v);
	Vector operator-() const;

	inline Vector operator*(const Vector &v) const;
	Vector operator*(const FPType s) const;
	inline Vector operator*=(const FPType s);
	inline Vector operator/(const FPType &s) const;
	Vector operator/(const Vector &v) const;
	Vector operator-(const Vector &v) const;
	Vector operator+(const Vector &v) const;

	const FPType& operator [] (uint8_t i) const
	{
		return (&x)[i];
	}
	FPType& operator [] (uint8_t i)
	{
		return (&x)[i];
	}

	FPType clamp1(const FPType &lo, const FPType &hi, const FPType &v);

	Vector SphericalToCartesian(const FPType &theta, const FPType &phi);
	inline FPType SphericalTheta(const Vector &v);
	inline FPType SphericalPhi(const Vector &v);
	inline FPType cosTheta(const Vector &w)
	{
		return w[2];
	}
	inline FPType sinTheta2(const Vector &w)
	{
		return std::max(FPType(0), 1 - cosTheta(w) * cosTheta(w));
	}
	inline FPType sinTheta(const Vector &w)
	{
		return sqrt(sinTheta2(w));
	}
	inline FPType cosPhi(const Vector &w)
	{
		FPType sintheta = sinTheta(w);
		if(sintheta == 0) return 1;
		return clamp1(w[0] / sintheta, -1, 1);
	}
	inline FPType sinPhi(const Vector &w)
	{
		FPType sintheta = sinTheta(w);
		if(sintheta == 0) return 0;
		return clamp1(w[1] / sintheta, -1, 1);
	}
};

