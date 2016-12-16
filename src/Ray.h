#pragma once
#include "Vector.h"

struct Ray
{
public:
	Ray();
	Ray(const Vector origin_, const Vector direction_);

	void SetOrigin(const Vector &origin_);
	void SetDirection(const Vector &direction_);
	Vector GetOrigin();
	Vector GetDirection();

	FPType tMin, tMax;

private:
	Vector origin, direction;
};