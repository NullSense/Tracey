#pragma once
#include "Globals.h"
#include "Object.h"

class Box : public Object
{
public:
	Box(const Vector3 &min_, const Vector3 &max_);
	FPType GetIntersection(const Ray ray);
	Vector3 GetIntersectionPoint(const Ray ray);
	Vector3 GetNormalAt(const Vector3 point);

private:
	Vector3 min;
	Vector3 max;
	Ray bRay;
};