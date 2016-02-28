#pragma once
#include "Globals.h"

class Color
{
public:
	FPType red, green, blue, specular, special;

	Color();
	Color(FPType red_, FPType green_, FPType blue_, FPType specular_ ,FPType special_);

	FPType Brightness();
	Color Scalar(const FPType &scalar);
	Color Average(const Color &color);
	Color operator*(const Color &color);
	Color operator+(const Color &color);

	Color Clip();
};