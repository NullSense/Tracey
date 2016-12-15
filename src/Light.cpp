#include "Light.h"

Light::Light()
	:position {0, 0, 0}
	, color {Color(255, 255, 255)}
	, intensity {2}
{}

Light::Light(Vector position_, Color color_, int intensity_)
	:position {position_}
	, color {color_}
	, intensity {intensity_}
{}

void Light::SetPosition(const Vector &position_)
{
	position = position_;
}

void Light::SetColor(const Color &color_)
{
	color = color_;
}

void Light::SetIntensity(const int &intensity_)
{
	intensity = intensity_;
}

Color Light::GetColor()
{
	return color;
}

Vector Light::GetPosition()
{
	return position;
}

int Light::GetIntensity()
{
	return intensity;
}
