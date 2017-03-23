#include "Object.h"

Object::Object() noexcept
{}

Object::~Object()
{}

FPType Object::GetIntersection(const Ray &)
{
	return 0;
}

Vector3d Object::GetNormalAt(const Vector3d &)
{
	return 0;
}