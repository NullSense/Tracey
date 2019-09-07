#include "Plane.h"

Plane::Plane() : center{0, -1, 0}, normal{1, 0, 0} {}

Plane::Plane(Vector3d center_, Vector3d normal_)
    : center{center_}, normal{normal_} {}

Vector3d Plane::GetNormalAt(const Vector3d &) { return normal; }

double Plane::GetIntersection(const Ray &ray) {
  double denom = normal.Dot(ray.GetDirection());
  if (std::fabs(denom) > BIAS) {
    double t = (center - ray.GetOrigin()).Dot(normal) / denom;
    if (t > BIAS) return t;
  }
  return false;
}

double Plane::GetIntersectionDisk(Ray ray, Vector3d normal_,
                                  Vector3d position) {
  double denom = normal_.Dot(ray.GetDirection());
  double t = -1;
  if (std::fabs(denom) > ray.tMin && t <= ray.tMax) {
    t = (position - ray.GetOrigin()).Dot(normal_) / denom;
  }
  return t;
}

Vector3d Plane::GetCenter() const { return center; }
