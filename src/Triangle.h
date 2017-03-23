#pragma once

#include "Vector3.h"
#include "Object.h"
#include "Ray.h"

class Triangle: public Object
{
public:
	Triangle();
	Triangle(Vector3d v0_, Vector3d v1_, Vector3d v2_);

	Vector3d GetNormalAt(const Vector3d &point);
	FPType GetIntersection(const Ray &ray);

	Vector3d v0, v1, v2;
	Vector3d normal;
private:
};