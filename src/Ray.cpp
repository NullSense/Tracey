#include "Ray.h"

Ray::Ray()
{
	origin = Vector(0, 0, 0);
	direction = Vector(0, 0, 1);
	tMin = TOLERANCE;
	tMax = 1000;
}

Ray::Ray(const Vector origin_, const Vector direction_)
{
	origin = origin_;
	direction = direction_;
	tMin = TOLERANCE;
	tMax = 1000;
}

void Ray::SetOrigin(const Vector &origin_)
{
	origin = origin_;
}

void Ray::SetDirection(const Vector &direction_)
{
	direction = direction_;
}

Vector Ray::GetOrigin()
{
	return origin;
}

Vector Ray::GetDirection()
{
	return direction;
}
