#include "Light.h"

Light::Light()
	:position {0, 0, 0}
	, color {Color(255, 255, 255)}
{}

Light::Light(Vector position_, Color color_)
	:position {position_}
	, color {color_}
{}

void Light::SetPosition(Vector position_)
{
	position = position_;
}

void Light::SetColor(Color color_)
{
	color = color_;
}

Color Light::GetColor()
{
	return color;
}

Vector Light::GetPosition()
{
	return position;
}
