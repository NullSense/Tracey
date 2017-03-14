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

Vector Sphere::GetNormalAt(const Vector point)
{
	// normal always points away from the center of a sphere 
	return (point - center).Normalize();
}

FPType Sphere::GetIntersection(Ray ray)
{
	Vector delta = ray.GetOrigin() - center;
	Vector dir = ray.GetDirection();

	//Quadratic equation describing the distance along ray to intersection
	FPType a = dir.Dot(dir);
	FPType b = dir.Dot(delta); //removed factor of 2 later divide by a, NOT 2a
	FPType c = delta.Dot(delta) - radius*radius;

	FPType discriminant = b*b - a*c;
	if (discriminant < FPType(0)) {
		return -1;
	}
	//Find solutions to quadratic equation
	discriminant = sqrt(discriminant) / a;
	b = -b / a;

	FPType intersection0 = b - discriminant;
	if(intersection0 >= FPType(0)) {
		return intersection0;
	}

	FPType intersection1 = b + discriminant;
	if(intersection1 >= FPType(0)) {
		return intersection1;
	}

	//Both solutions were negative
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
