#include "Vector3.h"

Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(const FPType x_, const FPType y_, const FPType z_)
{
	x = x_;
	y = y_;
	z = z_;
}

Vector3::Vector3(const FPType value)
{
	x = value;
	y = value;
	z = value;
}

FPType Vector3::clamp1(const FPType lo, const FPType hi, const FPType v)
{
	return std::max(lo, std::min(hi, v));
}

Vector3 Vector3::Normalize()
{
	FPType length = Dot(*this);
	if(length > 0)
	{
		FPType invLength = 1 / sqrt(length);
		x *= invLength, y *= invLength, z *= invLength;
	}
	return *this;
}

FPType Vector3::Magnitude()
{
	return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

FPType Vector3::Dot(const Vector3 &v) const
{
	return (this->x * v.x + this->y * v.y + this->z * v.z);
}

Vector3 Vector3::Cross(const Vector3 &v) const
{
	return Vector3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}

Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator*(const FPType s) const
{
	return Vector3(x * s, y * s, z * s);
}

Vector3 Vector3::operator*(const Vector3 &v) const
{
	return Vector3(x * v.x, y * v.y, z * v.z);
}

Vector3 Vector3::operator*=(const FPType s)
{
	x *= s, y *= s, z *= s;
	return *this;
}

Vector3 Vector3::operator/(const FPType s) const
{
	return Vector3(x / s, y / s, z / s);
}

Vector3 Vector3::operator/(const Vector3 &v) const
{
	return Vector3(x / v.x, y / v.y, z / v.z);
}

Vector3 Vector3::operator-(const Vector3 &v) const
{
	return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator+(const Vector3 &v) const
{
	return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::SphericalToCartesian(const FPType theta, const FPType phi)
{
	return Vector3(cos(phi) * sin(theta), sin(phi) * sin(theta), cos(theta));
}

inline FPType Vector3::SphericalTheta(const Vector3 &v)
{
	return acos(clamp1(v[2], -1, 1));
}

inline FPType Vector3::SphericalPhi(const Vector3 &v)
{
	FPType p = atan2(v[1], v[0]);
	return (p < 0) ? p + 2 * M_PI : p;
}

