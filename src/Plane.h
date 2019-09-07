#pragma once

#include "Object.h"
#include "Ray.h"
#include "Vector3.h"

class Plane : public Object {
 public:
  Plane();
  Plane(Vector3d center_, Vector3d normal_);

  virtual Vector3d GetNormalAt(const Vector3d &point);
  virtual double GetIntersection(const Ray &ray);
  double GetIntersectionDisk(const Ray ray, const Vector3d normal_,
                             const Vector3d position);
  Vector3d GetCenter() const;

 private:
  Vector3d normal, center;
};
