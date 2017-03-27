#include "Sphere.h"

Sphere::Sphere()
{
	radius = 1;
	center = Vector3d(1, 1, 1);
}

Sphere::Sphere(FPType radius_, Vector3d center_)
{
	radius = radius_;
	center = center_;
}

Vector3d Sphere::GetNormalAt(const Vector3d &point)
{
	// normal always points away from the center of a sphere 
	return (point - center).Normalize();
}

FPType Sphere::GetIntersection(const Ray &ray)
{
	Vector3d delta = ray.GetOrigin() - center;
	Vector3d dir = ray.GetDirection();

	//Quadratic equation describing the distance along ray to intersection
	FPType a = dir.Dot(dir);
	FPType b = dir.Dot(delta); //removed factor of 2 later divide by a, NOT 2a
	FPType c = delta.Dot(delta) - radius*radius;

	FPType discriminant = b*b - a*c;
	if(discriminant < FPType(0))
	{
		return -1;
	}
	//Find solutions to quadratic equation
	discriminant = sqrt(discriminant) / a;
	b = -b / a;

	FPType intersection0 = b - discriminant;
	if(intersection0 >= FPType(0))
	{
		return intersection0;
	}

	FPType intersection1 = b + discriminant;
	if(intersection1 >= FPType(0))
	{
		return intersection1;
	}

	//Both solutions were negative
	return -1;
}

Vector3d Sphere::GetTexCoords(Vector3d &normal, const Vector3d &hitPoint)
{
	normal = hitPoint - center;
	normal.Normalize();

	Vector3d tex;
	tex.x = (1 + atan2(normal.z, normal.x) / M_PI) * 0.5;
	tex.y = acos(normal.y) / M_PI;
	return tex;
}

FPType Sphere::GetRadius() const
{
	return radius;
}

Vector3d Sphere::GetCenter() const
{
	return center;
}
