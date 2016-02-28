#include "Object.h"

Object::Object() noexcept
{}

FPType Object::GetIntersection(Ray ray)
{
	return 0;
}

Vector Object::GetNormalAt(Vector intersectionPosition)
{
	return Vector(0, 0, 0);
}

Color Object::GetColor()
{
	//return color;

	return Color(0, 0, 0, 0, 0);
}