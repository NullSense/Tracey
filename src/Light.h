#pragma once

#include "Vector.h"
#include "Color.h"

struct Light
{
public:
	Light();

	Light(Vector position_, Color material_, int intensity_);

	void SetPosition(const Vector &position_);
	void SetColor(const Color &color_);
	void SetIntensity(const int &intensity_);
	Color GetColor();
	Vector GetPosition();
	int GetIntensity();

private:
	Color color;
	Vector position;
	int intensity;
};