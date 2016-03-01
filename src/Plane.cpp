#include "Plane.h"

Plane::Plane()
	:normal {1, 0, 0}
	, center {0, -1, 0}
{
}

Plane::Plane(Vector center_, Vector normal_)
	:normal {normal_}
	, center {center_}
{
}

FPType Plane::GetIntersection(Ray ray)
{
	FPType denom = normal.Dot(ray.direction);
	FPType t;
	if(abs(denom) > 0.0001) // epsilon <3
	{
		t = (center - ray.origin).Dot(normal) / denom;
	}
	return t;
}

Vector Plane::GetNormalAt(Vector point)
{
	return normal;
}