#include "Color.h"

Color::Color()
	:red {0}
	, green {0}
	, blue {0}
	, specular {0}
	, special {0}
{}

Color::Color(FPType red_, FPType green_, FPType blue_, FPType specular_, FPType special_)
	: red {red_}
	, green {green_}
	, blue {blue_}
	, specular {specular_}
	, special {special_}
{}

Color Color::Clip()
{
	FPType alllight = red + green + blue;
	FPType excesslight = alllight - 765; // 255 * 3 = 765

	if(excesslight > 0)
	{
		red = red + excesslight * (red / alllight);
		green = green + excesslight * (green / alllight);
		blue = blue + excesslight * (blue / alllight);
	}
	if(red > 255)
	{
		red = 255;
	}
	if(green > 255)
	{
		green = 255;
	}
	if(blue > 255)
	{
		blue = 255;
	}
	if(red < 0)
	{
		red = 0;
	}
	if(green < 0)
	{
		green = 0;
	}
	if(blue < 0)
	{
		blue = 0;
	}

	return Color(red, green, blue, specular, special);
}

FPType Color::Brightness()
{
	return (red + green + blue) / 3;
}

Color Color::Scalar(const FPType &scalar)
{
	return Color(red * scalar, green * scalar, blue * scalar, specular, special);
}

Color Color::Average(const Color &color)
{
	return Color((red + color.red) / 2, (green + color.green) / 2, specular, (blue + color.blue) / 2, special);
}

Color Color::operator*(const Color &color)
{
	return Color((red * color.red), (green * color.green), (blue * color.blue), specular, special);
}

Color Color::operator+(const Color &color)
{
	return Color((red + color.red), (green + color.green), (blue + color.blue), specular, special);
}
