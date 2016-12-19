#include "Box.h"

Box::Box(const Vector &min_, const Vector &max_)
{
	min = min_;
	max = max_;
}

FPType Box::GetIntersection(Ray ray)
{
	FPType tx1 = (min.x - ray.GetOrigin().x) * ray.invDir.x;
	FPType tx2 = (max.x - ray.GetOrigin().x) * ray.invDir.x;

	FPType tmin = std::fmin(tx1, tx2);
	FPType tmax = std::fmax(tx1, tx2);

	FPType ty1 = (min.y - ray.GetOrigin().y) * ray.invDir.y;
	FPType ty2 = (max.y - ray.GetOrigin().y) * ray.invDir.y;

	tmin = std::fmax(tmin, std::fmin(ty1, ty2));
	tmax = std::fmin(tmax, std::fmax(ty1, ty2));

	return tmax >= tmin;
}