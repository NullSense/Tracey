#pragma once
#include "Globals.h"
#include <cmath>

struct Vector
{
public:
	FPType x, y, z;

	Vector(FPType x_, FPType y_, FPType z_);
	Vector();

	Vector Normalize();
	inline FPType Magnitude();
	FPType Dot(const Vector &v);
	Vector Cross(const Vector &v);
	Vector Negative();

	inline Vector operator*(const Vector &v);
	Vector operator*(const FPType &s);
	inline Vector operator*=(const FPType &s);
	inline Vector operator/(const FPType &s);
	Vector operator-(const Vector &v);
	Vector operator+(const Vector &v);
};

