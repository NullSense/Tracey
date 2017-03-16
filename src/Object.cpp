#include "Object.h"

Object::Object() noexcept
{}

Object::~Object()
{
}

FPType Object::GetIntersection(const Ray ray)
{
	return 0;
}

Vector Object::GetNormalAt(const Vector intersectionPosition)
{
	return Vector(0, 0, 0);
}