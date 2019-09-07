#include "Light.h"

Light::Light()
    : position{0}, color{Color(255)}, intensity{1}, light_type{POINT} {}

Light::Light(Vector3d position_, Color color_, double intensity_,
             enum LIGHT_TYPES)
    : position{position_},
      color{color_},
      intensity{intensity_},
      light_type{POINT} {}

void Light::SetPosition(const Vector3d &position_) { position = position_; }

void Light::SetColor(const Color &color_) { color = color_; }

void Light::SetIntensity(const double intensity_) { intensity = intensity_; }

Color Light::GetColor() { return color; }

Vector3d Light::GetPosition() { return position; }

double Light::GetIntensity() { return intensity; }

unsigned Light::GetLightType() { return 0; }
