#pragma once
#include "Globals.h"

struct Color
{
public:
	FPType red, green, blue;

	Color();
	Color(FPType red_, FPType green_, FPType blue_);

	Color Average(const Color &color);
	Color operator*(const Color &color);
	Color operator*(const FPType &scalar);
	Color operator*=(const FPType &scalar);
	Color operator+(const Color &color);
	Color operator+=(const Color &color);

	Color Clip();
};