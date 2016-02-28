#pragma once
#include "Globals.h"
#include <cmath>

class Vector
{
public:
	FPType x, y, z;

	Vector(FPType x_, FPType y_, FPType z_);
	Vector();

	Vector Normalize();
	FPType Magnitude();
	FPType Dot(const Vector &v);
	Vector Cross(const Vector &v);
	Vector Negative();

	Vector operator*(const Vector &v);
	Vector operator*(const FPType &s);
	Vector operator/(const FPType &s);
	Vector operator-(const Vector &v);
	Vector operator+(const Vector &v);
};

