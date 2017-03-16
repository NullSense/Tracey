#pragma once

#include "Vector3.h"
#include "Color.h"

struct Light
{
public:
	enum LIGHT_TYPES
	{
		POINT = 1, DISK = 2, AREA = 3
	} light_type;

	Light();

	Light(Vector3 position_, Color color_, FPType intensity_, enum LIGHT_TYPES);


	void SetPosition(const Vector3 &position_);
	void SetColor(const Color &color_);
	void SetIntensity(const FPType intensity_);
	Color GetColor();
	Vector3 GetPosition();
	FPType GetIntensity();
	unsigned GetLightType();

private:
	Color color;
	Vector3 position;
	FPType intensity;
};