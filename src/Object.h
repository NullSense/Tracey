#pragma once
#include "Vector.h"
#include "Ray.h"
#include "Color.h"
#include "Material.h"

class Object : public Material
{
public:
	Object() noexcept;

	virtual FPType Object::GetIntersection(Ray ray);

	virtual Vector GetNormalAt(Vector intersectionPosition);

	virtual Color GetColor();

	Material GetMaterial();

	void SetMaterial(Material material_);

private:
	Material material;
};
