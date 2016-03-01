#pragma once

#include "Vector.h"
#include "Material.h"

struct Light : public Material
{
public:
	Light();

	Light(Vector position_, Material material_);

	void SetPosition(Vector position_);
	void SetMaterial(Material material_);
	Material GetMaterial();
	Vector GetPosition();

private:
	Material material;
	Vector position;
};