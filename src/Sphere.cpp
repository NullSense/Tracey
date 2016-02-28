#include "Sphere.h"

Sphere::Sphere()
{
	radius = 1;
	position = Vector(1, 1, 1);
	color = Color(155, 155, 155, 0);
}

Sphere::Sphere(FPType radius_, Vector position_, Color color_)
{
	radius = radius_;
	position = position_;
	color = color_;
}

Color Sphere::GetColor()
{
	return color;
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

	Vector p = ray.origin - position; // the vector from the sphere's center to the ray source
	b = -(p.Dot(ray.direction));

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
