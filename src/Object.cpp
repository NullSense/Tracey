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

Vector3d Object::GetNormalAt(const Vector3d intersectionPosition)
{
	return Vector3d(0);
}