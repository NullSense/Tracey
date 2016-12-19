#include "Disk.hpp"

Disk::Disk(Vector position_, FPType radius_, Vector normal_)
	:position{position_}, radius{radius_}, normal{normal_}
{}

FPType Disk::GetIntersection(Ray ray)
{

	if(Plane::GetIntersectionDisk(ray, GetNormal(), position))
	{
		FPType t = Plane::GetIntersectionDisk(ray, GetNormal(), position);
		Vector intersectionPoint = ray.GetOrigin() + ray.GetDirection() * t;
		Vector intersectionToMidDist = intersectionPoint - position;
		FPType d2 = intersectionToMidDist.Dot(intersectionToMidDist);
		FPType radius2 = radius * radius;
		return d2 <= radius2;
	}
	else
		return -1;
}

Vector Disk::GetNormalAt(Vector point)
{
	return normal;
}

Vector Disk::GetNormal() const
{
	return normal;
}

Vector Disk::GetPosition() const
{
	return position;
}

void Disk::SetNormal(const Vector & normal_)
{
	normal = normal;
}

void Disk::SetPosition(const Vector & position_)
{
	position = position_;
}
