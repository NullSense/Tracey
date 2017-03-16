#include "Box.h"

Box::Box(const Vector3d &min_, const Vector3d &max_)
{
	min = min_;
	max = max_;
}

FPType Box::GetIntersection(Ray ray)
{
	Vector3d origin = ray.GetOrigin();
	Vector3d direction = ray.GetDirection();
	Vector3d invDirection = ray.invDir;

	FPType t1 = (min.x - origin.x) * invDirection.x;
	FPType t2 = (max.x - origin.x) * invDirection.x;
	FPType t3 = (min.y - origin.y) * invDirection.y;
	FPType t4 = (max.y - origin.y) * invDirection.y;
	FPType t5 = (min.z - origin.z) * invDirection.z;
	FPType t6 = (max.z - origin.z) * invDirection.z;

	FPType tboxmin = std::fmax(std::fmax(std::fmin(t1, t2), std::fmin(t3, t4)), std::fmin(t5, t6));
	FPType tboxmax = std::fmin(std::fmin(std::fmax(t1, t2), std::fmax(t3, t4)), std::fmax(t5, t6));

	if(tboxmax < BIAS)
	{
		return false;
	}

	if(tboxmin > tboxmax)
	{
		return false;
	}
	bRay = ray;

	return tboxmax >= tboxmin;
}

Vector3d Box::GetIntersectionPoint(Ray ray)
{
	FPType t = GetIntersection(ray);
	return (ray.GetOrigin() + ray.GetDirection() * t);
}

Vector3d Box::GetNormalAt(const Vector3d point)
{
	Vector3d c = (min + max) * 0.5;
	Vector3d p = GetIntersectionPoint(bRay) - c;
	Vector3d d = (min - max) * 0.5;
	FPType bias = 1.000001;

	return Vector3d((p / d) * bias).Normalize();
}
