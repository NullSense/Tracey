#pragma once
#include "Color.h"

class Material : public Color {
 public:
  Material() {}

  Material(Color color_, double ambient_ = 1, double reflective_ = 0,
           double refractive_ = 0, double diffusive_ = 1, double special_ = 0)
      : color{color_},
        ambient{ambient_},
        reflective{reflective_},
        refractive{refractive_},
        diffusive{diffusive_},
        special{special_} {}

  void SetColor(const Color &color_) { color = color_; }
  void SetDiffuse(const double &diffusive_) { diffusive = diffusive_; }
  void SetReflection(const double &reflective_) { reflective = reflective_; }
  void SetRefraction(const double &refractive_) { refractive = refractive_; }
  void SetSpecial(const double &special_) { special = special_; }

  Color GetColor() { return color; }
  double GetAmbient() { return ambient; }
  double GetSpecular() { return 1 - diffusive; }
  double GetDiffuse() { return diffusive; }
  double GetReflection() { return reflective; }
  double GetRefraction() const { return this->refractive; }
  double GetSpecial() { return special; }

  void SetMaterial(const Material &material_) { *this = material_; }
  Material GetMaterial() { return *this; }

 private:
  Color color;
  double ambient;
  double reflective;
  double refractive;
  double diffusive;  // The more diffusive it is, the better it scatters light
                     // (phong shading radius gets wider)
  double special;    // Tile floor
};
