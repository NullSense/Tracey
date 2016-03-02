#pragma once

#include "Vector.h"
#include "Color.h"

struct Light
{
public:
	Light();

	Light(Vector position_, Color material_);

	void SetPosition(Vector position_);
	void SetColor(Color color_);
	Color GetColor();
	Vector GetPosition();

private:
	Color color;
	Vector position;
};