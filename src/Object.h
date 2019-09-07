#pragma once
#include "Color.h"
#include "Material.h"
#include "Ray.h"
#include "Vector3.h"

class Object {
 public:
  Object() noexcept;
  virtual ~Object();

  virtual double GetIntersection(const Ray &ray);
  virtual Vector3d GetNormalAt(const Vector3d &intersectionPosition);
  virtual Vector3d GetTexCoords(Vector3d &normal, const Vector3d &hitPoint);

  Material material;
};
