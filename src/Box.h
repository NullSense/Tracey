#pragma once
#include "Globals.h"
#include "Object.h"

class Box : public Object
{
public:
	Box(const Vector3d &min_, const Vector3d &max_);
	FPType GetIntersection(const Ray ray);
	Vector3d GetIntersectionPoint(const Ray ray);
	Vector3d GetNormalAt(const Vector3d point);

private:
	Vector3d min;
	Vector3d max;
	Ray bRay;
};