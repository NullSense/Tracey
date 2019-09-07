#pragma once
#include "Object.h"
#include "Vector3.h"

class Sphere : public Object {
 public:
  Sphere();
  Sphere(double radius_, Vector3d center_);

  Vector3d GetNormalAt(const Vector3d &point);
  double GetIntersection(const Ray &ray);
  double GetRadius() const;
  Vector3d GetCenter() const;
  Vector3d GetTexCoords(Vector3d &normal, const Vector3d &hitPoint);

 private:
  double radius;
  Vector3d center;
};
