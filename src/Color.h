#pragma once
#include "Globals.h"

class Color
{
public:
	FPType red, green, blue, special;

	Color();
	Color(FPType red_, FPType green_, FPType blue_, FPType special_);

	FPType Brightness();
	Color Scalar(const FPType &scalar);
	Color Average(const Color &color);
	Color operator*(const Color &color);
	Color operator+(const Color &color);

	Color Clip();
};