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

	Light(Vector3d position_, Color color_, FPType intensity_, enum LIGHT_TYPES);


	void SetPosition(const Vector3d &position_);
	void SetColor(const Color &color_);
	void SetIntensity(const FPType intensity_);
	Color GetColor();
	Vector3d GetPosition();
	FPType GetIntensity();
	unsigned GetLightType();

private:
	Color color;
	Vector3d position;
	FPType intensity;
};