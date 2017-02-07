#pragma once

#include "Vector.h"
#include "Object.h"
#include "Ray.h"

class Triangle : public Object
{
public:
	Triangle();

	Vector GetNormal(Vector v0, Vector v1, Vector v2);
	Vector GetNormalAt(const Vector point);
	FPType GetIntersection(Ray ray);

private:
	Vector v0, v1, v2;
	Vector normal;
};
