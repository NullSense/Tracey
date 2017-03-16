#include "Ray.h"

Ray::Ray()
{
	origin = Vector3d(0);
	direction = Vector3d(0, 0, 1);
	tMin = BIAS;
	tMax = 1000;

	invDir.x = 1 / direction.x;
	invDir.y = 1 / direction.y;
	invDir.z = 1 / direction.z;

	sign[0] = (invDir.x < 0);
	sign[1] = (invDir.y < 0);
	sign[2] = (invDir.z < 0);
}

Ray::Ray(const Vector3d origin_, const Vector3d direction_)
{
	origin = origin_;
	direction = direction_;
	tMin = BIAS;
	tMax = 1000;

	invDir.x = 1 / direction_.x;
	invDir.y = 1 / direction_.y;
	invDir.z = 1 / direction_.z;

	sign[0] = (invDir.x < 0);
	sign[1] = (invDir.y < 0);
	sign[2] = (invDir.z < 0);
}

void Ray::SetOrigin(const Vector3d &origin_)
{
	origin = origin_;
}

void Ray::SetDirection(const Vector3d &direction_)
{
	direction = direction_;
}

Vector3d Ray::GetOrigin()
{
	return origin;
}

Vector3d Ray::GetDirection()
{
	return direction;
}
