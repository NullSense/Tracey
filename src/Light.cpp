#include "Light.h"

Light::Light()
	:position {0, 0, 0}
	, color {Color(255, 255, 255)}
	, intensity {1}
	, light_type {POINT}
{}

Light::Light(Vector position_, Color color_, FPType intensity_, enum LIGHT_TYPES)
	:position {position_}
	, color {color_}
	, intensity {intensity_}
	, light_type{POINT}
{}

void Light::SetPosition(const Vector &position_)
{
	position = position_;
}

void Light::SetColor(const Color &color_)
{
	color = color_;
}

void Light::SetIntensity(const FPType intensity_)
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

FPType Light::GetIntensity()
{
	return intensity;
}

unsigned Light::GetLightType()
{
	return 0;
}
