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