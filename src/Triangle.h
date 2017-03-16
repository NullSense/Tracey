#pragma once

#include "Vector3.h"
#include "Object.h"
#include "Ray.h"

class Triangle : public Object
{
public:
	Triangle();
	Triangle(Vector3 v0_, Vector3 v1_, Vector3 v2_);

	Vector3 GetNormal();
	Vector3 GetNormalAt(const Vector3 point);
	FPType GetIntersection(const Ray ray);

private:
	Vector3 v0, v1, v2;
	Vector3 normal;
};
