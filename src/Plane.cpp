#include "Plane.h"

Plane::Plane()
	:distance {0}
	, normal {1, 0, 0}
	, center {0, -1, 0}
{
	color = Color(0, 0, 255, 0);
}

Plane::Plane(Vector center_, FPType distance_, Vector normal_, Color color_)
	:distance {distance_}
	, normal {normal_}
	, center {center_}
{
	color = color_;
}

FPType Plane::GetIntersection(Ray ray)
{
	FPType denom = normal.Dot(ray.direction);
	FPType t;
	if(abs(denom) > ACCURACY) // ACCURACY == 0.000001
	{
		t = (center - ray.origin).Dot(normal) / denom;
	}
	return t;
}

Color Plane::GetColor()
{
	return color;
}

Vector Plane::GetNormalAt(Vector point)
{
	return normal;
}