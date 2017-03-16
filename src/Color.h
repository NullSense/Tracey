#pragma once
#include "Globals.h"

class Color
{
public:
	Color();
	Color(const FPType red_, const FPType green_, const FPType blue_);
	Color(const FPType color);

	FPType GetRed();
	FPType GetGreen();
	FPType GetBlue();

	void SetRed(const FPType red_);
	void SetGreen(const FPType green_);
	void SetBlue(const FPType blue_);

	Color Clip();
	Color Average(const Color &color);
	Color operator/(const FPType scalar);
	Color operator*(const Color &color);
	Color operator*(const FPType scalar);
	Color operator*=(const FPType scalar);
	Color operator+(const Color &color);
	Color operator+=(const Color &color);

	Color operator+=(const FPType a);

private:
	FPType red, green, blue;
};