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
	Vector length = position - ray.GetOrigin();
	FPType tc = length.Dot(ray.GetDirection());
	
	FPType intersectionPoint1;
	FPType intersectionPoint2;
	
	if(tc < 0) // No intersection registered
	{
		return -1;
	}
	if(tc > 0) // Intersection registered
	{
		FPType discriminant = sqrt(length*length - tc*tc);
		if(discriminant >= 0 && discriminant <= 1)
		{
			FPType thc = sqrt(radius*radius - discriminant*discriminant);
			intersectionPoint1 = tca - thc
			if(intersectionPoint1 > 0)
			{
				return intersectionPoint1;
			}
			else
			{
				intersectionPoint2 = thc + tc;
				return intersectionPoint2;
			}
		}
	}
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
