#include "Light.h"

Light::Light()
	:position {0, 0, 0}
	, material {Color(255, 255, 255), 0, 0, 0}
{}

Light::Light(Vector position_, Material material_)
	:position {position_}
	, material {material_}
{}

void Light::SetPosition(Vector position_)
{
	position = position_;
}

void Light::SetMaterial(Material material_)
{
	material = material_;
}

Material Light::GetMaterial()
{
	return material;
}

Vector Light::GetPosition()
{
	return position;
}
