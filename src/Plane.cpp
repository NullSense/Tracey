#include "Plane.h"

Plane::Plane()
	:center {0, -1, 0}
	, normal {1, 0, 0}
{}

Plane::Plane(Vector3d center_, Vector3d normal_)
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

FPType Plane::GetIntersectionDisk(Ray ray, Vector3d normal_, Vector3d position)
{
	FPType denom = normal_.Dot(ray.GetDirection());
	FPType t = -1;
	if(std::abs(denom) > ray.tMin && t <= ray.tMax)
	{
		t = (position - ray.GetOrigin()).Dot(normal_) / denom;
	}
	return t;
}

Vector3d Plane::GetCenter() const
{
	return center;
}

Vector3d Plane::GetNormalAt(const Vector3d point)
{
	return normal;
}