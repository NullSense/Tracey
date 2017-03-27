#pragma once

#include "Vector3.h"
#include "Object.h"
#include "Ray.h"

class Triangle: public Object
{
public:
	Triangle();
	Triangle(Vector3d &v0_, Vector3d &v1_, Vector3d &v2_);

	Vector3d GetNormalAt(const Vector3d &point) override;
	FPType GetIntersection(const Ray &ray, FPType &u, FPType &v);

	Vector3d v0, v1, v2;
private:
	Vector3d normal;
};