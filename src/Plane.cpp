#include "Plane.h"

Plane::Plane()
	:center {0, -1, 0}
	, normal {1, 0, 0}
{}

Plane::Plane(Vector center_, Vector normal_)
	:center {center_}
	, normal {normal_}
{}

FPType Plane::GetIntersection(Ray ray)
{
	FPType denom = normal.Dot(ray.GetDirection());
	if(std::abs(denom) > BIAS) // your favorite epsilon
	{
		FPType t = (center - ray.GetOrigin()).Dot(normal) / denom;
		if(t > BIAS)
			return t; // you might want to allow an epsilon here too
	}
	return false;
}

FPType Plane::GetIntersectionDisk(Ray ray, Vector normal_, Vector position)
{
	FPType denom = normal_.Dot(ray.GetDirection());
	FPType t = -1;
	if(std::abs(denom) > ray.tMin && t <= ray.tMax)
	{
		t = (position - ray.GetOrigin()).Dot(normal_) / denom;
	}
	return t;
}

Vector Plane::GetCenter() const
{
	return center;
}

Vector Plane::GetNormalAt(const Vector point)
{
	return normal;
}