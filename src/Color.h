#pragma once
#include "Globals.h"

class Color
{
public:
	Color();
	Color(FPType red_, FPType green_, FPType blue_);

	FPType GetRed();
	FPType GetGreen();
	FPType GetBlue();

	void SetRed(const FPType &red_);
	void SetGreen(const FPType &green_);
	void setBlue(const FPType &blue_);

	Color Clip();
	Color Average(const Color &color);
	Color operator/(const FPType & scalar);
	Color operator*(const Color &color);
	Color operator*(const FPType &scalar);
	Color operator*=(const FPType &scalar);
	Color operator+(const Color &color);
	Color operator+=(const Color &color);

	Color operator+=(const FPType & a);

private:
	FPType red, green, blue;
};