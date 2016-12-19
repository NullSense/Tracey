#include "Object.h"

Object::Object() noexcept
{}

Object::~Object()
{
	//std::cout << "Destroyed";
}

FPType Object::GetIntersection(Ray ray)
{
	return 0;
}

Vector Object::GetNormalAt(Vector intersectionPosition)
{
	return Vector(0, 0, 0);
}

Vector Object::GetNormal() const
{
	return normal;
}

Color Object::GetColor()
{
	return material.GetColor();
}

Material Object::GetMaterial()
{
	return material;
}

void Object::SetMaterial(const Material &material_)
{
	material = material_;
}