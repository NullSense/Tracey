#pragma once
#include "Globals.h"

class Color {
 public:
  Color();
  Color(const double red_, const double green_, const double blue_);
  Color(const double color);

  double GetRed();
  double GetGreen();
  double GetBlue();

  void SetRed(const double red_);
  void SetGreen(const double green_);
  void SetBlue(const double blue_);

  Color Clip();
  Color Average(const Color &color);
  Color operator/(const double scalar);
  Color operator*(const Color &color);
  Color operator*(const double scalar);
  Color operator*=(const double scalar);
  Color operator+(const Color &color);
  Color operator+=(const Color &color);

  Color operator+=(const double a);

 private:
  double red, green, blue;
};
