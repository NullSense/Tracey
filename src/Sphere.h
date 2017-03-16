#pragma once
#include "Vector3.h"
#include "Object.h"

class Sphere: public Object
{
public:
	Sphere();
	Sphere(FPType radius_, Vector3d center_);

	Vector3d GetNormalAt(const Vector3d point);
	FPType GetIntersection(const Ray ray);
	FPType GetRadius() const;
	Vector3d GetCenter() const;

private:
	FPType radius;
	Vector3d center;
};
