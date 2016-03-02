#pragma once
#include "Vector.h"

struct Ray
{
public:
	Ray();
	Ray(Vector origin_, Vector direction_);

	void SetOrigin(const Vector &origin_);
	void SetDirection(const Vector &direction_);
	Vector GetOrigin();
	Vector GetDirection();

private:
	Vector origin, direction;
};