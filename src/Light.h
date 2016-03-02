#pragma once

#include "Vector.h"
#include "Color.h"

struct Light
{
public:
	Light();

	Light(Vector position_, Color material_);

	void SetPosition(const Vector &position_);
	void SetColor(const Color &color_);
	Color GetColor();
	Vector GetPosition();

private:
	Color color;
	Vector position;
};