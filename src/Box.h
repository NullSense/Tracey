#pragma once
#include "Globals.h"
#include "Object.h"

class Box : public Object
{
public:
	Box(const Vector &min_, const Vector &max_);
	FPType GetIntersection(Ray ray);

private:
	Vector min;
	Vector max;
};