#include "Sphere.h"

Sphere::Sphere()
{
	radius = 1;
	center = Vector(1, 1, 1);
}

Sphere::Sphere(FPType radius_, Vector center_)
{
	radius = radius_;
	center = center_;
}

Vector Sphere::GetNormalAt(Vector point)
{
	// normal always points away from the center of a sphere 
	return (point - center).Normalize();
}

FPType Sphere::GetIntersection(Ray ray)
{
	Vector length = center - ray.GetOrigin(); // Length of the vector between the center and the ray origin (hypotenuse)
	FPType tca = length.Dot(ray.GetDirection()); // opposide side

	if(tca < 0) // No intersection registered
		return -1;

	if(tca > 0) // Intersection registered
	{
		FPType a = sqrt(length.Dot(length) - tca*tca); // Adjacent side (a = sqrt(c²-b²))

		if(a > radius || a < 0)
			return -1;

		FPType thc = sqrt(radius*radius - a*a); // the line between 2 intersection points / 2

		FPType primaryIntersection;
		primaryIntersection = tca - thc;
		if(primaryIntersection > 0)
			return primaryIntersection;
		else
		{
			FPType secondaryIntersection = thc + tca;
			return secondaryIntersection;
		}
	}
	return -1;
}

FPType Sphere::GetRadius() const
{
	return radius;
}

Vector Sphere::GetCenter() const
{
	return center;
}

void Sphere::SetRadius(const FPType &radius_)
{
	radius = radius_;
}

void Sphere::SetCenter(const Vector &center_)
{
	center = center_;
}
