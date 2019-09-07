#pragma once

#include "Color.h"
#include "Vector3.h"

struct Light {
 public:
  enum LIGHT_TYPES { POINT = 1, DISK = 2, AREA = 3 } light_type;

  Light();

  Light(Vector3d position_, Color color_, double intensity_, enum LIGHT_TYPES);

  void SetPosition(const Vector3d &position_);
  void SetColor(const Color &color_);
  void SetIntensity(const double intensity_);
  Color GetColor();
  Vector3d GetPosition();
  double GetIntensity();
  unsigned GetLightType();

 private:
  Color color;
  Vector3d position;
  double intensity;
};
