#pragma once

#include "Object.h"
#include "Ray.h"
#include "Vector3.h"

class Triangle : public Object {
 public:
  Triangle();
  Triangle(Vector3d &v0_, Vector3d &v1_, Vector3d &v2_);

  Vector3d GetNormalAt(const Vector3d &point);
  double GetIntersection(const Ray &ray, double &u, double &v);

  Vector3d v0, v1, v2;

 private:
  Vector3d normal;
};
