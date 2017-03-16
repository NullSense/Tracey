#pragma once
#include "Vector.h"
#include "Ray.h"
#include "Color.h"
#include "Material.h"

class Object: public Material
{
public:
	Object() noexcept;
	virtual ~Object();

	virtual FPType GetIntersection(const Ray ray);

	virtual Vector GetNormalAt(const Vector intersectionPosition);
};