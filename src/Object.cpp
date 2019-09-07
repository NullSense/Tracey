#include "Object.h"

Object::Object() noexcept {}

Object::~Object() {}

double Object::GetIntersection(const Ray &) { return 0; }

Vector3d Object::GetNormalAt(const Vector3d &) { return 0; }

Vector3d Object::GetTexCoords(Vector3d &, const Vector3d &) { return 0; }
