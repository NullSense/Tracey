#include "Sphere.h"

Sphere::Sphere()
{
	radius = 1;
	position = Vector(1, 1, 1);
}

Sphere::Sphere(FPType radius_, Vector position_)
{
	radius = radius_;
	position = position_;
}

Vector Sphere::GetNormalAt(Vector point)
{
	// normal always points away from the center of a sphere
	Vector normalAtPoint = (point - position).Normalize();
	return normalAtPoint;
}

FPType Sphere::GetIntersection(Ray ray)
{
	FPType discriminant, b;

	Vector p = ray.GetOrigin() - position; // the vector from the sphere's center to the ray source
	b = -(p.Dot(ray.GetDirection()));

	discriminant = (b * b) - p.Dot(p) + (radius * radius);

	if(discriminant > 0)
	{
		//calculate the two values for t
		FPType t1 = b - sqrt(discriminant);
		if(t1 > 0) // If t1 is closer to the ray source, return it
			return t1;
		else // If t2 is closer to the ray source, return it
		{
			FPType t2 = b + sqrt(discriminant);
			return t2;
		}
	}
	else //if it's less than 0, there's no intersection, return -1
		return -1;
}

FPType Sphere::GetRadius()
{
	return radius;
}

Vector Sphere::GetPosition()
{
	return position;
}

void Sphere::SetRadius(const FPType &radius_)
{
	radius = radius_;
}

void Sphere::SetPosition(const Vector &position_)
{
	position = position_;
}
