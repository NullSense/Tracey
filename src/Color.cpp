#include "Color.h"

Color::Color() : red{0}, green{0}, blue{0} {}

Color::Color(const double red_, const double green_, const double blue_)
    : red{red_}, green{green_}, blue{blue_} {}

Color::Color(const double color) : red{color}, green{color}, blue{color} {}

double Color::GetRed() { return red; }

double Color::GetGreen() { return green; }

double Color::GetBlue() { return blue; }

void Color::SetRed(const double red_) { red = red_; }

void Color::SetGreen(const double green_) { green = green_; }

void Color::SetBlue(const double blue_) { blue = blue_; }

Color Color::Clip() {
  double alllight = red + green + blue;
  double excesslight = alllight - 765;  // 255 * 3 = 765

  if (excesslight > 0) {
    red = red + excesslight * (red / alllight);
    green = green + excesslight * (green / alllight);
    blue = blue + excesslight * (blue / alllight);
  }
  if (red > 255) red = 255;

  if (green > 255) green = 255;

  if (blue > 255) blue = 255;

  if (red < 0) red = 0;

  if (green < 0) green = 0;

  if (blue < 0) blue = 0;

  return Color(red, green, blue);
}

Color Color::Average(const Color &color) {
  return Color((red + color.red) / 2, (green + color.green) / 2,
               (blue + color.blue) / 2);
}

Color Color::operator/(const double scalar) {
  return Color((red / scalar), (green / scalar), (blue / scalar));
}

Color Color::operator*(const double scalar) {
  return Color((red * scalar), (green * scalar), (blue * scalar));
}

Color Color::operator*(const Color &color) {
  return Color((red * color.red), (green * color.green), (blue * color.blue));
}

Color Color::operator+(const Color &color) {
  return Color((red + color.red), (green + color.green), (blue + color.blue));
}

Color Color::operator+=(const Color &color) {
  return Color(red += color.red, blue += color.blue, green += color.green);
}

Color Color::operator+=(const double a) {
  return Color(red += a, blue += a, green += a);
}

Color Color::operator*=(const double scalar) {
  return Color((red *= scalar), (green *= scalar), (blue *= scalar));
}
