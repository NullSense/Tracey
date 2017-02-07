#pragma once
#include "Vector.h"
#include "Object.h"

class Sphere: public Object
{
public:
	Sphere();
	Sphere(FPType radius_, Vector center_);

	Vector GetNormalAt(const Vector point);
	FPType GetIntersection(Ray ray);
	FPType GetRadius() const;
	Vector GetCenter() const;

private:
	FPType radius;
	Vector center;
};
