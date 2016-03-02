#pragma once
#include "Vector.h"
#include "Object.h"

class Sphere: public Object
{
public:
	Sphere();
	Sphere(FPType radius_, Vector position_);

	Vector GetNormalAt(Vector point);
	virtual FPType GetIntersection(Ray ray);
	FPType GetRadius();
	Vector GetPosition();
	void SetRadius(const FPType &radius_);
	void SetPosition(const Vector &position_);

private:
	FPType radius;
	Vector position;
};
