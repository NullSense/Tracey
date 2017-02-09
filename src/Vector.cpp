#include "Vector.h"

//FPType clamp(const FPType &lo, const FPType &hi, const FPType &v)
//{
//	return std::max(lo, std::min(hi, v));
//}

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

FPType Vector::clamp1(const FPType &lo, const FPType &hi, const FPType &v)
{
	return std::max(lo, std::min(hi, v));
}

Vector Vector::Normalize()
{
	FPType length = Dot(*this);
	if(length > 0)
	{
		FPType invLength = 1 / sqrt(length);
		x *= invLength, y *= invLength, z *= invLength;
	}
	return *this;
}

FPType Vector::Magnitude()
{
	return sqrt(x * x + y * y + z * z);
}

FPType Vector::Dot(const Vector &v)
{
	return (x * v.x + y * v.y + z * v.z);
}

Vector Vector::Cross(const Vector &v)
{
	return Vector(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}

Vector Vector::operator-() const
{
	return Vector(-x, -y, -z);
}

Vector Vector::operator*(const FPType s) const
{
	return Vector(x * s, y * s, z * s);
}

Vector Vector::operator*(const Vector &v) const
{
	return Vector(x * v.x, y * v.y, z * v.z);
}

Vector Vector::operator*=(const FPType s)
{
	x *= s, y *= s, z *= s;
	return *this;
}

Vector Vector::operator/(const FPType &s) const
{
	return Vector(x / s, y / s, z / s);
}

Vector Vector::operator/(const Vector &v) const
{
	return Vector(x / v.x, y / v.y, z / v.z);
}

Vector Vector::operator-(const Vector &v) const
{
	return Vector(x - v.x, y - v.y, z - v.z);
}

Vector Vector::operator+(const Vector &v) const
{
	return Vector(x + v.x, y + v.y, z + v.z);
}

Vector Vector::SphericalToCartesian(const FPType &theta, const FPType &phi)
{
	return Vector(cos(phi) * sin(theta), sin(phi) * sin(theta), cos(theta));
}

inline FPType Vector::SphericalTheta(const Vector & v)
{
	return acos(clamp1(v[2], -1, 1));
}

inline FPType Vector::SphericalPhi(const Vector & v)
{
	FPType p = atan2(v[1], v[0]);
	return (p < 0) ? p + 2 * M_PI : p;
}

