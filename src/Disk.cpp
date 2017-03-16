#include "Disk.hpp"

Disk::Disk()
{
	radius = 1;
	position = Vector3(0, 1, 8);
	normal = Vector3(0, 0, 1);
}

Disk::Disk(FPType radius_, Vector3 position_, Vector3 normal_)
	:radius {radius_}, position{position_}, normal{normal_}
{}

FPType Disk::GetIntersection(Ray ray)
{
	if(Plane::GetIntersectionDisk(ray, normal, position))
	{
		FPType t = Plane::GetIntersectionDisk(ray, normal, position);
		Vector3 intersectionPoint = ray.GetOrigin() + ray.GetDirection() * t;
		Vector3 intersectionToMidDist = intersectionPoint - position;
		FPType d2 = intersectionToMidDist.Dot(intersectionToMidDist);
		FPType radius2 = radius * radius;
		return (d2 <= radius2);
	}
	else
		return false;
}

Vector3 Disk::GetNormalAt(const Vector3 point)
{
	return normal;
}

Vector3 Disk::GetPosition() const
{
	return position;
}
