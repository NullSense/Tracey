#pragma once
#include "Vector3.h"

struct Ray
{
public:
	Ray();
	Ray(const Vector3 origin_, const Vector3 direction_);

	void SetOrigin(const Vector3 &origin_);
	void SetDirection(const Vector3 &direction_);
	Vector3 GetOrigin();
	Vector3 GetDirection();

	Vector3 invDir;
	FPType tMin, tMax;
private:
	Vector3 origin, direction;
	int sign[3];
};