#pragma once
#include "Vector3.h"
#include "Object.h"

class Sphere: public Object
{
public:
	Sphere();
	Sphere(FPType radius_, Vector3d center_);

	Vector3d GetNormalAt(const Vector3d &point);
	FPType GetIntersection(const Ray &ray);
	FPType GetRadius() const;
	Vector3d GetCenter() const;
	Vector3d GetTexCoords(Vector3d &normal, const Vector3d &hitPoint);

private:
	FPType radius;
	Vector3d center;
};
