#pragma once

#include "Vector.h"
#include "Color.h"

struct Light
{
public:
	Light();

	Light(Vector position_, Color color_, FPType intensity_);

	void SetPosition(const Vector &position_);
	void SetColor(const Color &color_);
	void SetIntensity(const FPType intensity_);
	Color GetColor();
	Vector GetPosition();
	FPType GetIntensity();

private:
	Color color;
	Vector position;
	FPType intensity;
};