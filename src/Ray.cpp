#include "Ray.h"

Ray::Ray()
{
	origin = Vector(0, 0, 0);
	direction = Vector(0, 0, 1);
	tMin = TOLERANCE;
	tMax = 1000;

	invDir.x = 1 / direction.x;
	invDir.y = 1 / direction.y;
	invDir.z = 1 / direction.z;

	sign[0] = (invDir.x < 0);
	sign[1] = (invDir.y < 0);
	sign[2] = (invDir.z < 0);
}

Ray::Ray(const Vector origin_, const Vector direction_)
{
	origin = origin_;
	direction = direction_;
	tMin = TOLERANCE;
	tMax = 1000;

	invDir.x = 1 / direction_.x;
	invDir.y = 1 / direction_.y;
	invDir.z = 1 / direction_.z;

	sign[0] = (invDir.x < 0);
	sign[1] = (invDir.y < 0);
	sign[2] = (invDir.z < 0);
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
