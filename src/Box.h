#pragma once
#include "Globals.h"
#include "Object.h"

class Box : public Object
{
public:
	Box(const Vector &min_, const Vector &max_);
	FPType GetIntersection(Ray ray);
	Vector GetIntersectionPoint(Ray ray);
	Vector GetNormalAt(const Vector point);

private:
	Vector min;
	Vector max;
	Ray bRay;
};