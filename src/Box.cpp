#include "Box.h"

Box::Box(const Vector &min_, const Vector &max_)
{
	min = min_;
	max = max_;
}

FPType Box::GetIntersection(Ray ray)
{
	Vector ro = ray.GetOrigin();
	Vector rd = ray.GetDirection();
	Vector rd_inv = ray.invDir;

	FPType t1 = (min.x - ro.x) * rd_inv.x;
	FPType t2 = (max.x - ro.x) * rd_inv.x;
	FPType t3 = (min.y - ro.y) * rd_inv.y;
	FPType t4 = (max.y - ro.y) * rd_inv.y;
	FPType t5 = (min.z - ro.z) * rd_inv.z;
	FPType t6 = (max.z - ro.z) * rd_inv.z;

	FPType tboxmin = std::fmax(std::fmax(std::fmin(t1, t2), std::fmin(t3, t4)), std::fmin(t5, t6));
	FPType tboxmax = std::fmin(std::fmin(std::fmax(t1, t2), std::fmax(t3, t4)), std::fmax(t5, t6));

	if(tboxmax < TOLERANCE)
	{
		return false;
	}

	if(tboxmin > tboxmax)
	{
		return false;
	}

	return tboxmax >= tboxmin;
}