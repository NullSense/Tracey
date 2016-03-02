#pragma once
#include "Vector.h"

struct Ray
{
public:
	Ray();
	Ray(Vector origin_, Vector direction_);

	void SetOrigin(Vector &origin_);
	void SetDirection(Vector &direction_);
	Vector GetOrigin();
	Vector GetDirection();

private:
	Vector origin, direction;
};