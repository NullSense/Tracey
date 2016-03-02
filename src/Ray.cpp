#include "Ray.h"

Ray::Ray()
{
	origin = Vector(0, 0, 0);
	direction = Vector(1, 0, 0);
}

Ray::Ray(Vector origin_, Vector direction_)
{
	origin = origin_;
	direction = direction_;
}

void Ray::SetOrigin(Vector & origin_)
{
	origin = origin_;
}

void Ray::SetDirection(Vector & direction_)
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
