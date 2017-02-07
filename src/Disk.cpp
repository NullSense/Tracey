#include "Disk.hpp"

Disk::Disk()
{
	radius = 1;
	position = Vector(0, 1, 8);
	normal = Vector(0, 0, 1);
}

Disk::Disk(FPType radius_, Vector position_, Vector normal_)
	:radius {radius_}, position{position_}, normal{normal_}
{}

FPType Disk::GetIntersection(Ray ray)
{
	if(Plane::GetIntersectionDisk(ray, normal, position))
	{
		FPType t = Plane::GetIntersectionDisk(ray, normal, position);
		Vector intersectionPoint = ray.GetOrigin() + ray.GetDirection() * t;
		Vector intersectionToMidDist = intersectionPoint - position;
		FPType d2 = intersectionToMidDist.Dot(intersectionToMidDist);
		FPType radius2 = radius * radius;
		return (d2 <= radius2);
	}
	else
		return false;
}

Vector Disk::GetNormalAt(const Vector point)
{
	return normal;
}

Vector Disk::GetPosition() const
{
	return position;
}
