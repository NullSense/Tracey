#pragma once
#include "Vector.h"
#include "Ray.h"
#include "Color.h"

class Object
{
public:
	Object() noexcept;

	Color color;

	virtual FPType Object::GetIntersection(Ray ray);

	virtual Vector GetNormalAt(Vector intersectionPosition);

	virtual Color GetColor();
};
