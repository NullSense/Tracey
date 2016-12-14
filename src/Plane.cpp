#include "Plane.h"

Plane::Plane()
	:normal {1, 0, 0}
	, center {0, -1, 0}
{}

Plane::Plane(Vector center_, Vector normal_)
	:normal {normal_}
	, center {center_}
{}

FPType Plane::GetIntersection(Ray ray)
{
	FPType denom = normal.Dot(ray.GetDirection());
	FPType t = -1;
	if(std::abs(denom) > 0.0001)
	{
		t = (center - ray.GetOrigin()).Dot(normal) / denom;
	}
	return t;
}

Vector Plane::GetNormal() const
{
	return normal;
}

Vector Plane::GetCenter() const
{
	return center;
}

void Plane::SetNormal(const Vector &normal_)
{
	normal = normal_;
}

void Plane::SetCenter(const Vector &center_)
{
	center = center_;
}

Vector Plane::GetNormalAt(const Vector point)
{
	return normal;
}