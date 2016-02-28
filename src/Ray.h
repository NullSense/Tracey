#pragma once
#include "Vector.h"

struct Ray
{
public:
	Ray();
	Ray(Vector origin_, Vector direction_);

	Vector origin, direction;
};