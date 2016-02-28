#pragma once

#include "Color.h"
#include "Vector.h"

struct Light
{
public:
	Light();

	Light(Vector position_, Color color_);

	Vector position;
	Color color;
};