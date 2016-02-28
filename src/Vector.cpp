#include "Vector.h"

Vector::Vector()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector::Vector(FPType x_, FPType y_, FPType z_)
{
	x = x_;
	y = y_;
	z = z_;
}

Vector Vector::Normalize()
{
	return Vector(x / Magnitude(), y / Magnitude(), z / Magnitude());
}

FPType Vector::Magnitude()
{
	return sqrt((x * x) + (y * y) + (z * z));
}

FPType Vector::Dot(const Vector &v)
{
	return (x * v.x + y * v.y + z * v.z);
}

Vector Vector::Cross(const Vector &v)
{
	return Vector(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}

Vector Vector::Negative()
{
	return Vector(-x, -y, -z);
}

Vector Vector::operator*(const FPType &s)
{
	return Vector(x * s, y * s, z * s);
}

Vector Vector::operator/(const FPType &s)
{
	return Vector(x / s, y / s, z / s);
}

Vector Vector::operator-(const Vector &v)
{
	return Vector(x - v.x, y - v.y, z - v.z);
}

Vector Vector::operator+(const Vector &v)
{
	return Vector(x + v.x, y + v.y, z + v.z);
}