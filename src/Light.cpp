
#include "Light.h"

Light::Light()
	:position {0, 0, 0}
	, color {255, 255, 255, 0}
{}

Light::Light(Vector position_, Color color_)
	:position {position_}
	, color {color_}
{}