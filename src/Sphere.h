#pragma once
#include "Vector3.h"
#include "Object.h"

class Sphere: public Object
{
public:
	Sphere();
	Sphere(FPType radius_, Vector3 center_);

	Vector3 GetNormalAt(const Vector3 point);
	FPType GetIntersection(const Ray ray);
	FPType GetRadius() const;
	Vector3 GetCenter() const;

private:
	FPType radius;
	Vector3 center;
};
