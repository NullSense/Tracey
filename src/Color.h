#pragma once
#include "Globals.h"

class Color
{
public:
	FPType red, green, blue;

	Color();
	Color(FPType red_, FPType green_, FPType blue_);

	FPType Brightness();
	Color Average(const Color &color);
	Color operator*(const Color &color);
	Color operator*(const FPType &scalar);
	Color operator*=(const FPType &scalar);
	Color operator+(const Color &color);
	Color operator+=(const Color &color);

	Color Clip();
};