#pragma once
#include "Vector.h"
#include "Object.h"

class Sphere: public Object
{
public:
	FPType radius;
	Vector position;

	Sphere();
	Sphere(FPType radius_, Vector position_);

	Vector GetNormalAt(Vector point);
	virtual FPType GetIntersection(Ray ray);
};
