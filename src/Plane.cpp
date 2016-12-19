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
	FPType t = -1;
	if(std::abs(denom) > ray.tMin && t <= ray.tMax)
	{
		t = (center - ray.GetOrigin()).Dot(normal) / denom;
	}
	return t;
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