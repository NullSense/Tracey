#include "Plane.h"

Plane::Plane()
	:center {0, -1, 0}
	, normal {1, 0, 0}
{}

Plane::Plane(Vector3 center_, Vector3 normal_)
	:center {center_}
	, normal {normal_}
{}

FPType Plane::GetIntersection(Ray ray)
{
	FPType denom = normal.Dot(ray.GetDirection());
	if(std::abs(denom) > BIAS)
	{
		FPType t = (center - ray.GetOrigin()).Dot(normal) / denom;
		if(t > BIAS)
			return t;
	}
	return false;
}

FPType Plane::GetIntersectionDisk(Ray ray, Vector3 normal_, Vector3 position)
{
	FPType denom = normal_.Dot(ray.GetDirection());
	FPType t = -1;
	if(std::abs(denom) > ray.tMin && t <= ray.tMax)
	{
		t = (position - ray.GetOrigin()).Dot(normal_) / denom;
	}
	return t;
}

Vector3 Plane::GetCenter() const
{
	return center;
}

Vector3 Plane::GetNormalAt(const Vector3 point)
{
	return normal;
}