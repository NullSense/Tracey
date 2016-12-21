#pragma once

#include "Vector.h"
#include "Color.h"

struct Light
{
public:
	enum LIGHT_TYPES
	{
		POINT = 1, DISK = 2, AREA = 3
	} light_type;

	Light();

	Light(Vector position_, Color color_, FPType intensity_, enum LIGHT_TYPES);


	void SetPosition(const Vector &position_);
	void SetColor(const Color &color_);
	void SetIntensity(const FPType intensity_);
	Color GetColor();
	Vector GetPosition();
	FPType GetIntensity();
	unsigned GetLightType();

private:
	Color color;
	Vector position;
	FPType intensity;
};