#pragma once
#include "Vector3.h"

struct Ray {
 public:
  Ray();
  Ray(const Vector3d origin_, const Vector3d direction_);

  void SetOrigin(const Vector3d &origin_);
  void SetDirection(const Vector3d &direction_);
  Vector3d GetOrigin() const;
  Vector3d GetDirection() const;

  Vector3d invDir;
  double tMin, tMax;
  int sign[3];

 private:
  Vector3d origin, direction;
};
