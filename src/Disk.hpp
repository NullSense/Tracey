#pragma once
#include "Globals.h"
#include "Plane.h"
#include "Ray.h"
#include "Vector3.h"

class Disk : public Plane {
 public:
  Disk();
  Disk(double radius_, Vector3d position_, Vector3d normal_);
  double GetIntersection(const Ray &ray);

  Vector3d GetNormalAt(const Vector3d &point);
  Vector3d GetPosition() const;

 private:
  Vector3d position;
  Vector3d normal;
  double radius;
};
